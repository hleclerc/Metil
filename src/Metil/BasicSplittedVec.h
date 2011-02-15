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


#ifndef BASIC_SPLITTED_VEC_H
#define BASIC_SPLITTED_VEC_H

// #include "BasicLst.h"
// #include "Stream.h"
#include "Malloc.h"
#include "Assert.h"

BEG_METIL_NAMESPACE

///
template<class T,int atomic_size,int size_first_item=atomic_size>
class BasicSplittedVec {
public:
    struct Item {
        Item *prev, *next;
        T *cur, *end;
        char *beg[ size_first_item * sizeof( T ) ];

        const T *ptr() const { return reinterpret_cast<const T *>( beg ); }
        T *ptr() { return reinterpret_cast<T *>( beg ); }

        const T &val( int n ) const { return reinterpret_cast<T *>( beg )[ n ]; }
        T &val( int n ) { return reinterpret_cast<T *>( beg )[ n ]; }

        ST size() const { return cur - ptr(); }
    };
    static const int base_item_size = sizeof( Item ) - sizeof( size_first_item );

    BasicSplittedVec() : last( &first ) {
        first.prev = 0;
        first.next = 0;
        first.cur = first.ptr();
        first.end = first.ptr() + size_first_item;
    }

    ~BasicSplittedVec() {
        for( Item *i = last ; i; ) {
            for( const T *p = i->cur - 1; p >= i->ptr(); --p )
                p->~T();
            Item *o = i;
            i = i->prev;
            if ( o != &first )
                FREE( o, reinterpret_cast<char *>( o->end ) - reinterpret_cast<char *>( o ) );
        }
    }

    template<class T2>
    BasicSplittedVec &operator<<( const T2 &val ) {
        push_back( val );
        return *this;
    }

    T *push_back() {
        T *res = get_room();
        new( res ) T;
        return res;
    }

    template<class T0>
    T *push_back( const T0 &v0 ) {
        T *res = get_room();
        new( res ) T( v0 );
        return res;
    }

    template<class T0,class T1>
    T *push_back( const T0 &v0, const T1 &v1 ) {
        T *res = get_room();
        new( res ) T( v0, v1 );
        return res;
    }

    template<class T0,class T1,class T2>
    T *push_back( const T0 &v0, const T1 &v1, const T2 &v2 ) {
        T *res = get_room();
        new( res ) T( v0, v1, v2 );
        return res;
    }

    template<class T0,class T1,class T2,class T3>
    T *push_back( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3 ) {
        T *res = get_room();
        new( res ) T( v0, v1, v2, v3 );
        return res;
    }

    template<class T0,class T1,class T2,class T3,class T4>
    T *push_back( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4 ) {
        T *res = get_room();
        new( res ) T( v0, v1, v2, v3, v4 );
        return res;
    }

    /// append val if not present and return pointer to new elem. Else, return pointer to elem which is equal to val
    template<class T2>
    T *push_back_unique( const T2 &val ) {
        for( ST i = 0; i < size(); ++i ) // TODO: optimize
            if ( operator[]( i ) == val )
                return &operator[]( i );
            return push_back( val );
    }

    /// TODO : optimize if POD
    void write( const T *d, SI64 s ) {
        for(int i=0;i<s;++i)
            operator<<( d[ i ] );
    }

    /// binary copy
    template<class R>
    void write_bin( const R &d ) {
        memcpy( get_room( sizeof( R ) / sizeof( T ) ), &d, sizeof( R ) );
    }

    template<class Op> void apply( Op &op ) const {
        for( const Item *i = &first; i; i = i->next )
            for( const T *p = i->ptr(); p < i->cur; ++p )
                op( *p );
    }

    template<class Op> void apply( Op &op ) {
        for( Item *i = &first; i; i = i->next )
            for( T *p = i->ptr(); p < i->cur; ++p )
                op( *p );
    }

    const T &back() const { return operator[]( size() - 1 ); }
    T &back() { return operator[]( size() - 1 ); }

    //    void write_to_stream( Stream &os ) const {
    //        Disp disp;
    //        disp.os = &os;
    //        apply( disp );
    //    }

    SI64 size() const {
        SI64 res = 0;
        for( const Item *i = &first; i; i = i->next )
            res += i->cur - i->ptr();
        return res;
    }

    void copy_to( T *d ) const {
        for( const Item *i = &first; i; i = i->next ) {
            SI64 s = i->cur - i->ptr();
            memcpy( d, i->beg, s );
            d += s;
        }
    }

    T operator[]( ST index ) const {
        for( const Item *i = &first; i; i = i->next ) {
            SI64 s = i->cur - i->ptr();
            if ( index < s )
                return i->val( index );
            index -= s;
        }
        ASSERT( 0, "index > size" );
        return *reinterpret_cast<T *>( 0 );
    }

    T &operator[]( ST index ) {
        for( Item *i = &first; i; i = i->next ) {
            SI64 s = i->cur - i->ptr();
            if ( index < s )
                return i->val( index );
            index -= s;
        }
        ASSERT( 0, "index > size" );
        return *reinterpret_cast<T *>( first.beg );
    }

    T *get_room( ST nb_elements = 1 ) {
        if ( last == 0 or last->cur + nb_elements + 1 > last->end )
            return get_room_in_new_Item( nb_elements );
        //
        T *res = last->cur;
        last->cur += nb_elements;
        return res;
    }

    T *get_room_in_new_Item( ST nb_elements ) {
        Item *old_last = last;
        ST rese = base_item_size + sizeof( T ) * ( nb_elements <= atomic_size ? atomic_size : nb_elements );
        last = reinterpret_cast<Item *>( MALLOC( rese ) );
        last->cur = last->ptr() + nb_elements;
        last->end = reinterpret_cast<T *>( reinterpret_cast<char *>( last ) + rese );
        last->prev = old_last;
        last->next = 0;
        if ( old_last )
            old_last->next = last;

        return last->ptr();
    }

    Item *last, first;
};

END_METIL_NAMESPACE

#endif // BASIC_SPLITTED_VEC_H
