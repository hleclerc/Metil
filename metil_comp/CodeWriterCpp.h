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

#ifndef METIL_CODEWRITERCPP_H
#define METIL_CODEWRITERCPP_H

#include "CodeWriter.h"
#include "CString.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file CodeWriterCpp.cpp
#endif

namespace Metil {

/**

*/
class CodeWriterCpp : public CodeWriter {
public:
    CodeWriterCpp( const String &filename, int nb_spaces = 0 );
    virtual void write_beg_for_loop( const Type *type_iter, const void *beg, const void *end, const void *step, int &loop_id, int &var_id );
    virtual void write_end_for_loop( int loop_id );
    virtual void write_header();
    virtual void write_footer();
    virtual void write_assign_and_inc_ptr( int ptr_id, int val_id );
    virtual int add_argument( const Type *type );
    virtual int execute( void **arguments );
    
    virtual void write_to_stream( Stream &stream ) const;
private:
    int new_var();
    int new_loop();
    
    int nb_var, nb_loop, nb_spaces;
    File code;
    CString cpp_file;
};


}

#endif // METIL_CODEWRITERCPP_H
