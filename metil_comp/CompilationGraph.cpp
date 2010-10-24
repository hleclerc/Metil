/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "CompilationGraph.h"
#include "CompilationCppParser.h"
#include "File.h"
#include "System.h"

#include <QtCore/QThread>
#include <QtCore/QMutex>


namespace Metil {

unsigned CompilationGraph::current_op_id = 0;

CompilationGraph::CompilationGraph() : date_last_modification_( 0 ), cpt_use( 0 ), op_id( 0 ) {
}

void CompilationGraph::decrease_cpt_use( CompilationGraph *cg ) {
    if ( not --cg->cpt_use )
        delete cg;
}

CompilationGraph::~CompilationGraph() {
    for(int i=0;i<children.size();++i)
        decrease_cpt_use( children[ i ] );
}

void CompilationGraph::add_child( CompilationGraph *cg ) {
    children.push_back( cg );
    cg->parents.push_back( this );
    ++cg->cpt_use;
}

void CompilationGraph::save( const String &gf ) {
    File os( gf.data(), "w" );
    save( os );
}

void CompilationGraph::save( Stream &gf ) {
    ++current_op_id;
    int n = 0;
    assign_number_rec( n );
    //
    ++current_op_id;
    save_rec( gf );
}

void CompilationGraph::save_rec( Stream &gf ) {
    if ( op_id == current_op_id )
        return;
    op_id = current_op_id;

    // children number
    gf << "->";
    for(int i=0;i<children.size();++i)
        gf << " " << children[i]->number;
    gf << Stream::endl << *this << Stream::endl;

    //
    for(int i=0;i<children.size();++i)
        children[i]->save_rec( gf );
}

void CompilationGraph::assign_number_rec( int &n ) {
    if ( op_id == current_op_id )
        return;
    op_id = current_op_id;
    //
    number = n++;
    for(int i=0;i<children.size();++i)
        children[ i ]->assign_number_rec( n );
}

CompilationGraph *CompilationGraph::load( const String &graph_filename ) {
    File is( graph_filename );
    return load( is );
}

CompilationGraph *CompilationGraph::load( const Stream &graph_istream ) {
    String line;
    return NULL;
}

BasicVec<CompilationGraph *> CompilationGraph::get_leaves() {
    BasicVec<CompilationGraph *> res;
    ++current_op_id;
    get_leaves_rec( res );
    return res;
}

void CompilationGraph::get_leaves_rec( BasicVec<CompilationGraph *> &res ) {
    if ( op_id == current_op_id )
        return;
    op_id = current_op_id;
    //
    if ( children.size() )
        for(int i=0;i<children.size();++i)
            children[ i ]->get_leaves_rec( res );
    else
        res.push_back( this );
}

bool CompilationGraph::all_children_have_op_id_equal_to_current() const {
    for(int i=0;i<children.size();++i)
        if ( children[ i ]->op_id != current_op_id )
            return false;
    return true;
}

bool CompilationGraph::necessary_to_make_node() const {
    long long d = date_last_modification();
    if ( d == 0 )
        return true; // there's no file
    //
    for(int i=0;i<children.size();++i)
        if ( children[ i ]->date_last_modification() > d )
            return true;
    return false;
}

class CG_Make : public QThread {
public:
    CG_Make() : global_res( 0 ) {}
    void run() {
        while ( front->size() ) {
            CompilationGraph *cg;

            mutex->lock();
                if ( not front->size() ) {
                    mutex->unlock();
                    break;
                }
                cg = front->back(); front->pop_back();
                if ( cg->op_id == CompilationGraph::current_op_id )
                    continue;
            mutex->unlock();

            if ( cg->necessary_to_make_node() ) {
                // do it
                int res = cg->make_node();
                if ( res )
                    global_res = res;
                // say
                for(int num_p=0;num_p<cg->parents.size();++num_p)
                    cg->parents[ num_p ]->date_last_modification_ = 0;
            }

            //
            mutex->lock();
                cg->op_id = CompilationGraph::current_op_id;
                for(int num_p=0;num_p<cg->parents.size();++num_p)
                    if ( cg->parents[ num_p ]->all_children_have_op_id_equal_to_current() )
                        front->push_back( cg->parents[ num_p ] );
                //
                if ( global_res )
                    front->resize( 0 );
            mutex->unlock();
        }
    }
    QMutex *mutex;
    BasicVec<CompilationGraph *> *front;
    int global_res;
};

int CompilationGraph::make() {
    BasicVec<CompilationGraph *> front = get_leaves();

    const int nb_threads = 4;
    CG_Make cg_make[ nb_threads ];
    QMutex mutex;
    for(int i=0;i<nb_threads;++i) {
        cg_make[i].mutex = &mutex;
        cg_make[i].front = &front;
    }

    //
    ++current_op_id;

    for(int i=0;i<nb_threads;++i)
        cg_make[i].start();

    for(int i=0;i<nb_threads;++i)
        cg_make[i].wait ();

    for(int i=0;i<nb_threads;++i)
        if ( cg_make[i].global_res )
            return cg_make[i].global_res;
    return 0;
}

String CompilationGraph::cmd_make_obj( const CompilationEnvironment &ce, const String &obj_filename, bool dynamic_object ) const {
    return "";
}

String CompilationGraph::get_filename() const {
    return "";
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphWithFilename::CompilationGraphWithFilename( const String &filename ) : filename( filename ) {
    date_last_modification_ = last_modification_time_or_zero_of_file_named( filename );
}

String CompilationGraphWithFilename::get_filename() const {
    return filename;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphProgram::CompilationGraphProgram( const CompilationEnvironment &ce, const String &exe_filename, bool dynamic_lib ) : CompilationGraphWithFilenameAndEnvironment( ce, exe_filename ), dynamic_lib( dynamic_lib ) {
}

void CompilationGraphProgram::write_to_stream( Stream &gf ) const {
    gf << "  program " << filename << "\n  " << get_cmd();
}

void CompilationGraphProgram::add_src_file( const String &src_file ) {
    if ( src_files.contains( src_file ) )
        return;
    src_files << src_file;

    // parse
    CompilationCppParser ccp_parser( ce, src_file );

    // -I...
    for(int i=0;i<ccp_parser.cpp_paths.size();++i)
        ce.add_include_dir( ccp_parser.cpp_paths[ i ] );
    for(int i=0;i<ccp_parser.lib_paths.size();++i)
        ce.add_library_dir( ccp_parser.lib_paths[ i ] );

    // add .o
    CompilationGraphObjFile *obj_item = new CompilationGraphObjFile( ce, ce.obj_file_for( src_file, dynamic_lib ), new CompilationGraphCppFile( src_file ), dynamic_lib );
    add_child( obj_item );

    // add .h dependendies to obj_item
    for(int i=0;i<ccp_parser.header_files.size();++i)
        obj_item->add_child( new CompilationGraphHeaderFile( ccp_parser.header_files[ i ] ) );

    // .h.py
    for(int i=0;i<ccp_parser.hdotpy_files.size();++i) {
        String hdotpy_file = ccp_parser.hdotpy_files[ i ];
        String header_file = hdotpy_file.rstrip( 3 );
        CompilationGraph *header_item = new CompilationGraphGeneratedHeaderFile( ce, header_file, hdotpy_file );
        CompilationGraph *python_item = new CompilationGraphPyFile( hdotpy_file );
        obj_item   ->add_child( header_item );
        header_item->add_child( python_item );
    }

    // .h.met
    for(int i=0;i<ccp_parser.hdotme_files.size();++i) {
        String hdotme_file = ccp_parser.hdotme_files[ i ];
        String header_file = hdotme_file.rstrip( 3 );
        CompilationGraph *header_item = new CompilationGraphGeneratedHeaderFile( ce, header_file, hdotme_file );
        CompilationGraph *metil_item = new CompilationGraphMeFile( hdotme_file );
        obj_item   ->add_child( header_item );
        header_item->add_child( metil_item  );
    }

    // -l
    for(int i=0;i<ccp_parser.extlib_names.size();++i)
        ce.add_library( ccp_parser.extlib_names[ i ] );

    // add "permanent" base cpp files
    String base_dir = ce.get_comp_dir() + "base";
    for(DirectoryIterator f( base_dir ); f; ++f ) {
        String fn = *f;
        if ( fn.ends_with(".cpp") )
            ccp_parser.extcpp_files << base_dir + '/' + fn;
    }

    // .cpp
    String dylib_file;
    if ( ccp_parser.extcpp_files.size() ) {
        if ( dynamic_lib ) {
            for(int i=0;i<ccp_parser.extcpp_files.size();++i)
                add_src_file( ccp_parser.extcpp_files[ i ] );
        } else {
            dylib_file = ce.lib_file_for( src_file, true );
            CompilationGraphProgram *dylib = new CompilationGraphProgram( ce, dylib_file, true );
            for(int i=0;i<ccp_parser.extcpp_files.size();++i) {
                //if ( ccp_parser.extcpp_files[ i ].ends_with( ".cu" ) )
                //    add_src_file( ccp_parser.extcpp_files[ i ] );
                //else
                dylib->add_src_file( ccp_parser.extcpp_files[ i ] );
            }
            add_child( dylib );
        }
    }

    // moc
    for(int i=0;i<ccp_parser.files_to_moc.size();++i) {
        String moc_file = ccp_parser.files_to_moc[ i ];
        String cpp_file = ce.moc_file_for( moc_file );
        String obj_file = ce.obj_file_for( cpp_file );

        if ( not src_files.contains( cpp_file ) ) {
            src_files << cpp_file;

            CompilationGraph *moc = new CompilationGraphHeaderFile( moc_file );
            CompilationGraph *cpp = new CompilationGraphGeneratedByMocCppFile( ce, cpp_file, moc );
            CompilationGraph *obj = new CompilationGraphObjFile( ce, obj_file, cpp );
            add_child( obj );
        }
    }

    // need_compilation_environment
    if ( ccp_parser.need_compilation_environment )
        add_src_file( ce.make_ExternCompilationEnvironment_file( dylib_file ) );
}

String CompilationGraphProgram::get_cmd() const {
    BasicVec<String> obj;
    for(int i=0;i<children.size();++i)
        if ( children[ i ]->is_an_object() )
            obj << children[ i ]->get_filename();
    if ( dynamic_lib )
        return ce.cmd_lib_link( filename, obj, true );
    return ce.cmd_exe_link( filename, obj );
}

int CompilationGraphProgram::make_node() {
    return ce.exec_cmd( get_cmd() );
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphObjFile::CompilationGraphObjFile( const CompilationEnvironment &ce, const String &obj_filename, CompilationGraph *src, bool dynamic_object ) :
        CompilationGraphWithFilenameAndEnvironment( ce, obj_filename ), dynamic_object( dynamic_object ) {
    add_child( src );
}

int CompilationGraphObjFile::make_node() {
    // assuming that there's only one definition (.cpp) file
    for(int i=0;i<children.size();++i) {
        String cmd = children[ i ]->cmd_make_obj( ce, filename, dynamic_object );
        if ( cmd.size() ) {
            int res = ce.exec_cmd( cmd );
            if ( res )
                return res;
        }
    }
    return 0;
}

void CompilationGraphObjFile::write_to_stream( Stream &gf ) const {
    gf << "  obj " << filename;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphHeaderFile::CompilationGraphHeaderFile( const String &filename ) : CompilationGraphWithFilename( filename ) {
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
String CompilationGraphCppFile::cmd_make_obj( const CompilationEnvironment &ce, const String &obj_filename, bool dynamic_object ) const {
    if ( filename.ends_with( ".cu" ) )
         return ce.cmd_cu_comp( obj_filename, filename, dynamic_object );
    return ce.cmd_cpp_comp( obj_filename, filename, dynamic_object );
}

void CompilationGraphCppFile::write_to_stream( Stream &gf ) const {
    gf << "  cpp " << filename;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphGeneratedHeaderFile::CompilationGraphGeneratedHeaderFile( const CompilationEnvironment &ce, const String &header_file, const String &python_file ) : CompilationGraphWithFilenameAndEnvironment( ce, header_file ), python_file( python_file ) {
}

int CompilationGraphGeneratedHeaderFile::make_node() {
    int res = ce.exec_cmd( "export PYTHONPATH=" + cur_dir() + ":$PYTHONPATH; python " + python_file + " > " + filename );
    if ( res )
        rm( filename );
    return res;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
CompilationGraphGeneratedByMocCppFile::CompilationGraphGeneratedByMocCppFile( const CompilationEnvironment &ce, const String &res, CompilationGraph *src_file ) : CompilationGraphCppFile( res ), src_file( src_file ), ce( ce ) {
    add_child( src_file );
}

void CompilationGraphGeneratedByMocCppFile::write_to_stream( Stream &gf ) const {
    gf << "  generated_by_moc " << filename;
}

int CompilationGraphGeneratedByMocCppFile::make_node() {
    return ce.exec_cmd( "/usr/bin/moc-qt4 -I. " + src_file->get_filename() + " -o " + filename );
}


}

