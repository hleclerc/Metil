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

#ifndef METIL_COMMON_FUNCTIONS_H
#define METIL_COMMON_FUNCTIONS_H

#include "StdOp.h"
#include <assert.h>

#define PRINT( A ) \
    Metil::coutn << "  " << #A << " -> " << (A)
#define PRINTN( A ) \
    Metil::coutn << "  " << #A << " ->\n" << (A)

#ifdef DEBUG
    #include <assert.h>
    #define ASSERT_IF_DEBUG( A ) if ( not (A) ) { Metil::cerrn << "assertion " << #A << " not checked (in " << __FILE__ << " line " << __LINE__ << ")"; assert( 0 ); }
#else
    #define ASSERT_IF_DEBUG( A ) 
#endif // DEBUG

#define ASSERT( A, txt ) if ( not (A) ) { Metil::cerrn << "assertion " << #A << " not checked (in " << __FILE__ << " line " << __LINE__ << ") -> " << txt; assert( 0 ); }

#ifndef DO_NOT_USE_METIL_NS
    namespace Metil { /* only for namespace declaration */ }
    using namespace Metil;
#endif

#endif // METIL_COMMON_FUNCTIONS_H
