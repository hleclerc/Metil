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

#ifndef METILMEMORY_H
#define METILMEMORY_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Memory.cpp
#endif

namespace Metil {

void *malloc( long size );
void *memalign( int alignment, long size );
void free( void *ptr );

template<class T> T *malloc_( long size ) { return (T *)malloc( sizeof( T ) * size ); }
template<class T> T *memalign_( int alignment, long size ) { return (T *)memalign( sizeof( T ) * alignment, sizeof( T ) * size ); }

}

#endif // METILMEMORY_H
