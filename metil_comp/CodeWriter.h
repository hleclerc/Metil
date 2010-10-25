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

#ifndef METIL_CODEWRITER_H
#define METIL_CODEWRITER_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CodeWriter.cpp
#endif

namespace Metil {

class Type;
class Stream;
class CompilationEnvironment;

/**
  Goal: write a function
*/
class CodeWriter {
public:
    CodeWriter();
    virtual ~CodeWriter();
    virtual void write_beg_for_loop( const Type *type_iter, const void *beg, const void *end, const void *step, int &loop_id, int &var_id ) = 0;
    virtual void write_end_for_loop( int loop_id ) = 0;
    virtual void write_to_stream( Stream &stream ) const = 0;
    virtual void write_header() = 0;
    virtual void write_footer() = 0;
    virtual void write_assign_and_inc_ptr( int ptr_id, int val_id ) = 0;
    virtual int add_argument( const Type *type ) = 0;
    virtual int execute( void **arguments ) = 0;
protected:
    BasicVec<const Type *> arguments;
};

extern CompilationEnvironment *default_compilation_environment;

}

#include "CodeWriterCpp.h"

#endif // METIL_CODEWRITER_H
