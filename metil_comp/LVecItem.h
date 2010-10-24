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

#ifndef METIL_LVECITEM_H
#define METIL_LVECITEM_H

#include "LazyObject.h"
#include "Range.h"
#include "Type.h"
#include "memory.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LVecItem.cpp
#endif

namespace Metil {

class ValItemeration;

/**

*/
class LVecItem : public LazyObject {
public:

    // LVecItem speficic
    virtual Int64 size() const {
        ASSERT( 0, "size() should be redefined" );
        return 0;
    }
    virtual const Type *type() const = 0;
};

/**

*/
template<class T>
class LVecItemT : public LVecItem {
public:
    LVecItemT() : _data( 0 ), _size( 0 ) {
    }

    virtual ~LVecItemT() {
        for(int i=_size-1;i>=0;--i)
            _data[i].~T();
        free( _data );
    }

    virtual bool done() const { return _data; }

    virtual const Type *type() const { return type_ptr( StructForType<T>() ); }

    virtual void write_to_stream( Stream &os ) const {
        ASSERT( _data, "write_to_stream on a 'not done' LVecItem" );
        if ( not _size )
            return;
        os << _data[ 0 ];
        for(int i=1;i<_size;++i)
            os << ' ' << _data[ i ];
    }

    void allocate( Int64 s ) const {
        _size = s;
        _data = (T *)malloc( sizeof( T ) * _size );
    }

    mutable T *_data;
    mutable Int64 _size;
};

///
template<class T>
class LVecItemRange : public LVecItemT<T> {
public:
    LVecItemRange( const Range<T> &range ) : range( range ) { }

    virtual void exec_node() const {
        this->allocate( size() );
        //
        int i = 0;
        for(T b=range.b;b<range.e;++b)
            this->_data[ i++ ] = b;
    }

    virtual Int64 size() const {
        return range.size();
    }
    
    Range<T> range;
    
};

///
//LVecItem *new_LVecItemBinaryOp( const ValItemeration *op, const LVecItem *a, const LVecItem *b, LVecItem::S o1 = 0, LVecItem::S o2 = 0, LVecItem::S size = 0 );
//LVecItem *new_LVecItemUnaryOp( const ValItemeration *op, const LVecItem *a );

}


#endif // METIL_LVECITEM_H
