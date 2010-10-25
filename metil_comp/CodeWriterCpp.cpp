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

#include "BasicVec.h"
#include "CodeWriterCpp.h"
#include "Type.h"
#include "CompilationEnvironment.h"
#include "AutoPtr.h"
#include "AbiData.h"

namespace Metil {

CodeWriterCpp::CodeWriterCpp( const String &filename, int nb_spaces ) : nb_var( 0 ), nb_loop( 0 ), nb_spaces( nb_spaces ), code( filename, "w" ), cpp_file( filename ) {
}

int CodeWriterCpp::new_var() {
    return nb_var++;
}

int CodeWriterCpp::new_loop() {
    return nb_loop++;
}

void CodeWriterCpp::write_beg_for_loop( const Type *type_iter, const void *beg, const void *end, const void *step, int &loop_id, int &var_id ) {
    var_id  = new_var ();
    loop_id = new_loop();
    code << Stream::Spaces( nb_spaces ) << "for("; type_iter->write_cpp_type( code );
    code << " R" << var_id << "=" ; type_iter->write_cpp_value( code, beg  );
    code << ";R" << var_id << "<" ; type_iter->write_cpp_value( code, end  );
    code << ";R" << var_id << "+="; type_iter->write_cpp_value( code, step );
    code << ") {\n";
    nb_spaces += 4;
}

void CodeWriterCpp::write_end_for_loop( int loop_id ) {
    nb_spaces -= 4;
    code << Stream::Spaces( nb_spaces ) << "}\n";
}

void CodeWriterCpp::write_to_stream( Stream &stream ) const {
    stream << "code";
}

int CodeWriterCpp::add_argument( const Type *type ) {
    arguments << type;
    return new_var();
}

void CodeWriterCpp::write_header() {
    // code << Stream::Spaces( nb_spaces ) << "#include \"File.h\"\n";
    code << Stream::Spaces( nb_spaces ) << "extern \"C\" void generated_function( void **arguments ) {\n";
    nb_spaces += 4;
    for(int i=0;i<arguments.size();++i) {
        code << Stream::Spaces( nb_spaces );
        arguments[i]->write_cpp_type( code );
        code << " &R" << i << " = *reinterpret_cast<";
        arguments[i]->write_cpp_type( code );
        code << " *>( arguments[ " << i << " ] );\n";
    }
}

void CodeWriterCpp::write_footer() {
    nb_spaces -= 4;
    code << Stream::Spaces( nb_spaces ) << "}\n";
}

void CodeWriterCpp::write_assign_and_inc_ptr( int ptr_id, int val_id ) {
    code << Stream::Spaces( nb_spaces ) << "*(R" << ptr_id << "++) = R" << val_id << ";\n";
}

typedef void ExtFuncSignature( void ** );

int CodeWriterCpp::execute( void **arguments ) {
    code.flush();
    //
    String obj_file = default_compilation_environment->obj_file_for( cpp_file, /*dynamic*/true );
    String lib_file = default_compilation_environment->lib_file_for( cpp_file, /*dynamic*/true );
    // make dynamic library
    int res_comp = default_compilation_environment->exec_cmd( default_compilation_environment->cmd_cpp_comp( obj_file, cpp_file, /*dynamic*/true ) );
    if ( res_comp )
        return res_comp;
    int res_link = default_compilation_environment->exec_cmd( default_compilation_environment->cmd_lib_link( lib_file, obj_file, /*dynamic*/true ) );
    if ( res_link )
        return res_link;
    // load symbol
    AutoPtr<AbiData> abi = AbiData::load( lib_file );
    ExtFuncSignature &f = *reinterpret_cast<ExtFuncSignature *>( abi->get_symbol( "generated_function" ) );
    if ( not &f )
        return 1;
    f( arguments );
    return 0;
}

}


