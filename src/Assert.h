/*
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License version 2 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESST FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#ifndef METIL_ASSERT_H
#define METIL_ASSERT_H

#include "Config.h"

BEG_METIL_NAMESPACE

struct Abort {
};

#ifdef __CUDACC__
    #define ASSERT_IF_DEBUG( A ) 
    #define ASSERT( A, txt, ... ) 
    #define ERROR( txt, ... ) 
    #define TODO ASSERT( 0, "TODO" )
#else
    void abort_or_throw();
    bool __disp_and_abort_if_not_cond__( bool cond, const char *txt, ... );
    bool __do_nothing__();
    #ifdef DEBUG
        #define ASSERT_IF_DEBUG( A ) Metil::__disp_and_abort_if_not_cond__( A, __FILE__, __LINE__, #A )
    #else
        #define ASSERT_IF_DEBUG( A ) Metil::__do_nothing__()
    #endif // DEBUG

    #define ASSERT( A, txt, ... ) Metil::__disp_and_abort_if_not_cond__( A, "%s:%i: assertion %s not checked -> " txt "\n", __FILE__, __LINE__, #A, ##__VA_ARGS__ )

    #define ERROR( txt, ... ) Metil::__disp_and_abort_if_not_cond__( 0, "%s:%i: " txt "\n", __FILE__, __LINE__, ##__VA_ARGS__ )

    #define TODO ASSERT( 0, "TODO" )
#endif

#ifdef NO_SIG_NAN
#define SIG_NAN
#else
#define SIG_NAN ERROR( "Nan creation" )
#endif

#define SIG_INF ERROR( "Inf creation" )
#define SIG_I   ERROR( "complex to real" )

END_METIL_NAMESPACE

#endif // METIL_ASSERT_H

