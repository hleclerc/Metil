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

#ifndef METIL_LMATITEM_H
#define METIL_LMATITEM_H

#include "LazyObject.h"
#include "Type.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LMatItem.cpp
#endif

namespace Metil {

class Type;

/**

*/
class LMatItem : public LazyObject {
public:
    virtual const Type *type() const = 0;

    virtual Int64 nb_rows() const = 0;
    virtual Int64 nb_cols() const = 0;
};

///
//LMatItem *new_LMatItemFunction( const Type *type_item, const void *function, Int64 nb_rows, Int64 nb_cols );

/**
*/
template<class T>
class LMatItemDense : public LMatItem {
public:
    LMatItemDense( Int64 nb_rows, Int64 nb_cols ) : _data( 0 ), _nb_rows( nb_rows ), _nb_cols( nb_cols ) {
        _nb_cols_storage = ceil( _nb_cols, type()->alignement() );
    }

    virtual ~LMatItemDense() {
        for(int r=0,o=0;r<_nb_rows;++r,o+=_nb_cols_storage-_nb_cols)
            for(int c=0;c<_nb_cols;++c)
                _data[ o ].~T();
        free( _data );
    }

    virtual bool done() const { return _data; }

    virtual const Type *type() const { return type_ptr( StructForType<T>() ); }

    virtual Int64 nb_rows() const { return _nb_rows; }
    virtual Int64 nb_cols() const { return _nb_cols; }

    void allocate() const {
        _data = (T *)malloc( sizeof( T ) * _nb_rows * _nb_cols_storage );
    }

    virtual void write_to_stream( Stream &os ) const {
        for(int r=0,o=0;r<_nb_rows;++r,o+=_nb_cols_storage-_nb_cols) {
            for(int c=0;c<_nb_cols;++c)
                os << ( c ? " " : "" ) << _data[ o ];
            os << "\n";
        }
    }

    mutable T *_data;
    Int64 _nb_rows;
    Int64 _nb_cols;
    Int64 _nb_cols_storage;
};


///
template<class T>
class LMatItemCst : public LMatItemDense<T> {
public:
    LMatItemCst( Int64 nb_rows, Int64 nb_cols, const T &val ) : LMatItemDense<T>( nb_rows, nb_cols ), val( val ) {
    }

    virtual void exec_node() const {
        this->allocate();
        //
        for(int r=0,o=0;r<this->_nb_rows;++r,o+=this->_nb_cols_storage-this->_nb_cols)
            for(int c=0;c<this->_nb_cols;++c)
                this->_data[ o ] = val;
    }

    T val;
};


/**
*/
//template<class T>
//class LMatItemSparse : public LMatItem {
//public:
//    LMatItemSparse( const Type *type, S nb_rows_, S nb_cols_ ) : LMatItem( type, nb_rows_, nb_cols_ ), data( 0 ) {
//    }
//
//    virtual ~LMatItemSparse() {
//
//    }
//
//    T *data;
//    S nb_rows_storage;
//};


}


#endif // METIL_LMATITEM_H
