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

#ifndef COMPILATIONGRAPH_H
#define COMPILATIONGRAPH_H

#include "CompilationEnvironment.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CompilationGraph.cpp
#endif

namespace Metil {

class Stream;

/**
    @author Hugo Leclerc <leclerc@lmt.ens-cachan.fr>

    Format:
        Dependancies (node numbers)
        Node Data

    TODO : check double objects (several ways to do the same object, ...)
*/
class CompilationGraph {
public:
    CompilationGraph();
    virtual ~CompilationGraph();

    void add_child( CompilationGraph *cg );
    int nb_children() const { return children.size(); }
    CompilationGraph *child( int i ) const { return children[ i ]; }

    long long date_last_modification() const { return date_last_modification_; }

    virtual void write_to_stream( Stream &gf ) const = 0;
    virtual String cmd_make_obj( const CompilationEnvironment &ce, const String &obj_filename, bool dynamic_object = false ) const; // @see CppFile, ...

    void save( const String &gf );
    void save( Stream &gf );
    static CompilationGraph *load( const String &graph_filename );
    static CompilationGraph *load( const Stream &graph_istream );

    int make();
    virtual int make_node() = 0;
    virtual bool necessary_to_make_node() const;

    virtual String get_filename() const;
    virtual bool is_an_object() const { return false; }

    BasicVec<CompilationGraph *> get_leaves();

//protected:
    void get_leaves_rec( BasicVec<CompilationGraph *> &res );
    bool all_children_have_op_id_equal_to_current() const;
    void save_rec( Stream &gf );
    void assign_number_rec( int &n );

    static void decrease_cpt_use( CompilationGraph *cg );

    BasicVec<CompilationGraph *> children;
    BasicVec<CompilationGraph *> parents;

    int number; // used to save and re-load
    long long date_last_modification_;

    int cpt_use; // 0 -> destroy
    mutable unsigned op_id;
    static unsigned current_op_id;
};

/**
*/
class CompilationGraphWithFilename : public CompilationGraph {
public:
    CompilationGraphWithFilename( const String &filename );
    virtual String get_filename() const;
protected:
    String filename;
};

/**
*/
class CompilationGraphWithFilenameAndEnvironment : public CompilationGraphWithFilename {
public:
    CompilationGraphWithFilenameAndEnvironment( const CompilationEnvironment &ce, const String &filename ) : CompilationGraphWithFilename( filename ), ce( ce ) {}

// protected:
    CompilationEnvironment ce;
};

/**
*/
class CompilationGraphProgram : public CompilationGraphWithFilenameAndEnvironment {
public:
    CompilationGraphProgram( const CompilationEnvironment &ce, const String &exe_filename, bool dynamic_lib = false );
    void add_src_file( const String &src_file );

    String get_cmd() const;

    virtual void write_to_stream( Stream &gf ) const;
    virtual bool is_an_object() const { return dynamic_lib; }

protected:
    virtual int make_node();
    BasicVec<String> src_files;
    bool dynamic_lib;
};

/**
*/
class CompilationGraphObjFile : public CompilationGraphWithFilenameAndEnvironment {
public:
    CompilationGraphObjFile( const CompilationEnvironment &ce, const String &obj_filename, CompilationGraph *src, bool dynamic_object = false );

    virtual void write_to_stream( Stream &gf ) const;
    virtual bool is_an_object() const { return true; }
protected:
    virtual int make_node();
    bool dynamic_object;
};



/**
*/
class CompilationGraphHeaderFile : public CompilationGraphWithFilename {
public:
    CompilationGraphHeaderFile( const String &filename );

    virtual void write_to_stream( Stream &gf ) const { gf << "  header " << filename; }
protected:
    virtual int make_node() { return 0; }
};

/**
*/
class CompilationGraphGeneratedHeaderFile : public CompilationGraphWithFilenameAndEnvironment {
public:
    CompilationGraphGeneratedHeaderFile( const CompilationEnvironment &ce, const String &header_file, const String &python_file );

    virtual void write_to_stream( Stream &gf ) const { gf << "  generated_header " << filename; }
protected:
    virtual int make_node();
    String python_file;
};

/**
*/
class CompilationGraphCppFile : public CompilationGraphWithFilename {
public:
    CompilationGraphCppFile( const String &res ) : CompilationGraphWithFilename( res ) {}

    void write_to_stream( Stream &gf ) const;
    virtual String cmd_make_obj( const CompilationEnvironment &ce, const String &obj_filename, bool dynamic_object ) const;
protected:
    virtual int make_node() { return 0; }
};

/**
*/
class CompilationGraphGeneratedByMocCppFile : public CompilationGraphCppFile {
public:
    CompilationGraphGeneratedByMocCppFile( const CompilationEnvironment &ce, const String &res, CompilationGraph *src_file );

    virtual void write_to_stream( Stream &gf ) const;
protected:
    virtual int make_node();
    CompilationGraph *src_file;
    CompilationEnvironment ce;
};

/**
*/
class CompilationGraphPyFile : public CompilationGraphWithFilename {
public:
    CompilationGraphPyFile( const String &filename ) : CompilationGraphWithFilename( filename ) {
        // coutn << filename;
    }

    virtual void write_to_stream( Stream &gf ) const { gf << "  python " << filename; }
protected:
    virtual int make_node() { return 0; }
};


}


#endif

