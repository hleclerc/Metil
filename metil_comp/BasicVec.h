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

#ifndef METIL_VEC_H
#define METIL_VEC_H

#include "Range.h"
#include "Memory.h"
#include <new>
#include "CommonFunctions.h"

namespace Metil {

/// @see Vec, Mat, ... constructors
struct SetSize {};

/**
    BasicVec<double> -> dynamic vector of doubles
    BasicVec<double,3> -> static vector of doubles, size = 3
    BasicVec<double,0> -> static vector of doubles, size = 0
    BasicVec<double,-1,4> -> dynamic vector with prereservation of size 4 : if size remains <= 4, no malloc are necessary
*/
template<class T,int s=-1,int p=0,int alignment=1>
class BasicVec;


/**
    static case
*/
template<class T_,int static_size_,int static_prer_,int alignment_>
class VecAncestor {
public:
    typedef T_ T;
    typedef int S;
    static const int static_size = static_size_;
    static const int static_prer = static_prer_;
    static const int alignment   = alignment_;

    VecAncestor() {}

    template<class T0>
    VecAncestor( const T0 &v0 ) {
        for(S i=0;i<static_size_;++i)
            _data[ i ] = v0;
    }

    template<class T0,class T1>
    VecAncestor( const T0 &v0, const T1 &v1 ) {
        ASSERT_IF_DEBUG( static_size_ == 2 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
    }

    template<class T0,class T1,class T2>
    VecAncestor( const T0 &v0, const T1 &v1, const T2 &v2 ) {
        ASSERT_IF_DEBUG( static_size_ == 3 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
    }

    VecAncestor( SetSize, int s ) { ASSERT_IF_DEBUG( s == static_size ); }

    template<class T0>
    VecAncestor( SetSize, int s, const T0 &v0 ) { ASSERT_IF_DEBUG( s == static_size ); for(S i=0;i<static_size;++i)  _data[ i ] = v0; }

    template<class T2>
    VecAncestor( const Range<T2> &r ) {
        T2 i = r.b;
        for(S j=0;j<static_size_;i+=r.s,++j)
            _data[ j ] = i;
    }

    template<class T0>
    VecAncestor( const VecAncestor &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(S i=0;i<static_size_;++i)
            _data[ i ] = v[ i ];
    }

    template<class T2,int s,int p>
    VecAncestor( const BasicVec<T2,s,p> &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(S i=0;i<static_size_;++i)
            _data[ i ] = v[ i ];
    }

    void operator=( const VecAncestor &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(S i=0;i<static_size_;++i)
            _data[ i ] = v[ i ];
    }

    template<class T2,int s,int p>
    void operator=( const BasicVec<T2,s,p> &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(S i=0;i<static_size_;++i)
            _data[ i ] = v[ i ];
    }

    int size() const {
        return static_size_;
    }

    int rese() const {
        return static_size_;
    }

    const T &operator[]( int i ) const {
        ASSERT_IF_DEBUG( i < s );
        return _data[ i ];
    }

    T &operator[]( int i ) {
        ASSERT_IF_DEBUG( i < s );
        return _data[ i ];
    }


    void resize( int new_size ) {
        ASSERT_IF_DEBUG( new_size == static_size_ );
    }

    void resize( int new_size, const T &val ) {
        ASSERT_IF_DEBUG( new_size == static_size_ );
    }

    void reserve( int new_rese ) {
        ASSERT_IF_DEBUG( new_size == static_size_ );
    }

    T *begin() { return _data; }
    T *end() { return _data + static_size_; }
    const T *begin() const { return _data; }
    const T *end() const { return _data + static_size_; }

    T *ptr() { return _data; }
    const T *ptr() const { return _data; }

    T &back() { return _data[ static_size_ - 1 ]; }
    const T &back() const { return _data[ static_size_ - 1 ]; }

    template<class T2>
    bool contains( const T2 &d ) const {
        for(int i=0;i<static_size_;++i)
            if ( _data[ i ] == d )
                return true;
        return false;
    }

private:
    T _data[ static_size_ ];
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
    dynamic case
*/
template<class T_,int static_prer_,int alignment_>
class VecAncestor<T_,-1,static_prer_,alignment_> {
public:
    typedef T_ T;
    typedef int S;
    typedef char C;
    static const int static_size = -1;
    static const int static_prer = static_prer_;
    static const int alignment   = alignment_;

    VecAncestor() : _size( 0 ), _rese( static_prer_ ), _data( static_prer_ ? reinterpret_cast<T *>( _prer ) : 0 ), owning( true ) {}

    template<class T0>
    VecAncestor( const T0 &v0 ) : _size( 1 ), _rese( 1 ), _data( _alloc( 1 ) ), owning( true ) {
        new( _data + 0 ) T_( v0 );
    }

    template<class T0,class T1>
    VecAncestor( const T0 &v0, const T1 &v1 ) : _size( 2 ), _rese( 2 ), _data( _alloc( 2 ) ), owning( true ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
    }

    template<class T0,class T1,class T2>
    VecAncestor( const T0 &v0, const T1 &v1, const T2 &v2 ) : _size( 3 ), _rese( 3 ), _data( _alloc( 3 ) ), owning( true ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
        new( _data + 2 ) T_( v2 );
    }

    template<class T0,class T1,class T2,class T3>
    VecAncestor( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3 ) : _size( 4 ), _rese( 4 ), _data( _alloc( 4 ) ), owning( true ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
        new( _data + 2 ) T_( v2 );
        new( _data + 3 ) T_( v3 );
    }

    VecAncestor( SetSize, S s ) : _size( s ), _rese( s ), _data( _alloc( s ) ), owning( true ) {
        for(S i=0;i<s;++i)
            new( _data + i ) T_;
    }

    VecAncestor( SetSize, S s, T *ptr ) : _size( s ), _rese( s ), _data( ptr ), owning( false ) {
    }

    template<class T0>
    VecAncestor( SetSize, S s, const T0 &v0 ) : _size( s ), _rese( s ), _data( _alloc( s ) ), owning( true ) {
        for(S i=0;i<s;++i)
            new( _data + i ) T_( v0 );
    }

    template<class T0,class T1>
    VecAncestor( SetSize, S s, const T0 &v0, const T1 &v1 ) : _size( s ), _rese( s ), _data( _alloc( s ) ), owning( true ) {
        for(S i=0;i<s;++i)
            new( _data + i ) T_( v0, v1 );
    }

    VecAncestor( const VecAncestor &v ) : _size( v.size() ), _rese( _size ), _data( _alloc( _size ) ), owning( true ) {
        for(S i=0;i<_size;++i)
            new( _data + i ) T_( v[ i ] );
    }

    template<class T2,int s,int p>
    VecAncestor( const BasicVec<T2,s,p> &v ) : _size( v.size() ), _rese( _size ), _data( _alloc( _size ) ), owning( true ) {
        for(S i=0;i<_size;++i)
            new( _data + i ) T_( v[ i ] );
    }

    VecAncestor( T_ *beg, T_ *end ) : _size( end - beg ), _rese( end - beg ), _data( _alloc( _size ) ), owning( true ) {
        for(S i=0;i<_size;++i)
            new( _data + i ) T_( beg[ i ] );
    }

    void operator=( const VecAncestor &v ) {
        owning = true;
        reserve( v._size );
        for(S i=_size;i>=v._size;--i) // destruction for i > v._size
            _data[ i ].~T();
        for(S i=0;i<min(_size,v._size);++i) // operator= for i < both
            _data[ i ] = v._data[ i ];
        for(S i=_size;i<v._size;++i) // placement new
            new( _data + i ) T_( v._data[ i ] );
        _size = v._size;
    }

    template<class T2,int s,int p>
    void operator=( const BasicVec<T2,s,p> &v ) {
        owning = true;
        reserve( v.size() );
        for(S i=_size;i>=v.size();--i) // destruction for i > v._size
            _data[ i ].~T();
        for(S i=0;i<min(_size,v.size());++i) // operator= for i < both
            _data[ i ] = v[ i ];
        for(S i=_size;i<v.size();++i) // placement new
            new( _data + i ) T_( v[ i ] );
        _size = v.size();
    }

    ~VecAncestor() {
        if ( owning ) {
            for(S i=_size-1;i>=0;--i)
                _data[ i ].~T_();
            _free( _data );
        }
    }


    const T &operator[]( int i ) const { ASSERT_IF_DEBUG( i < s ); return _data[ i ]; }

    T &operator[]( int i ) { ASSERT_IF_DEBUG( i < s ); return _data[ i ]; }

    S size() const { return _size; }

    template<class T2>
    VecAncestor &operator<<( const T2 &val ) { push_back( val ); return *this; }

    T *push_back() {
        reserve_wm( _size + 1 );
        return _data + _size++;
    }

    template<class T0>
    T *push_back( const T0 &v0 ) {
        reserve_wm( _size + 1 );
        new( _data + _size ) T_( v0 );
        return _data + _size++;
    }

    template<class T0,class T1>
    T *push_back( const T0 &v0, const T1 &v1 ) {
        reserve_wm( _size + 1 );
        new( _data + _size ) T_( v0, v1 );
        return _data + _size++;
    }

    template<class T0,class T1,class T2>
    T *push_back( const T0 &v0, const T1 &v1, const T2 &v2 ) {
        reserve_wm( _size + 1 );
        new( _data + _size ) T_( v0, v1, v2 );
        return _data + _size++;
    }

    void reserve_wm( S wanted ) { // if not enough, reserve more than wanted...
        if ( wanted <= _rese )
            return;
        _mv_data_for_size( max( wanted, 2 * ( _rese + 1 ) ) );
    }

    void reserve( S wanted ) {
        if ( wanted <= _rese )
            return;
        _mv_data_for_size( wanted );
    }

    int rese() const { return _rese; }

    void resize( int new_size ) {
        reserve( new_size );
        for(int i=_size;i<new_size;++i)
            new( _data + i ) T;
        _size = new_size;
    }

    template<class T0>
    void resize( int new_size, const T0 &v0 ) {
        reserve( new_size );
        for(int i=_size;i<new_size;++i)
            new( _data + i ) T( v0 );
        _size = new_size;
    }

    template<class T0,class T1>
    void resize( int new_size, const T0 &v0, const T1 &v1 ) {
        reserve( new_size );
        for(int i=_size;i<new_size;++i)
            new( _data + i ) T( v0, v1 );
        _size = new_size;
    }

    void pop_back() {
        _data[ --_size ].~T();
    }

    // append val if not present and return pointer to new elem. Else, return pointer to elem which is equal to val
    template<class T2>
    T *push_back_unique( const T2 &val ) {
        for(int i=0;i<_size;++i)
            if ( _data[ i ] == val )
                return _data + i;
        return push_back( val );
    }

    // assumes that room for val that will be constructed is already reserved
    template<class T0>
    T *push_back_in_reserved( const T0 &v0 ) {
        T *res = _data + _size++;
        new( res ) T( v0 );
        return res;
    }

    // erase first element equal to val
    void remove_first_unordered( const T &val ) {
        for(int i=0;i<_size;++i) {
            if ( _data[ i ] == val ) {
                if ( i + 1 != _size )
                    _data[ i ] = back();
                pop_back();
                return;
            }
        }
    }

    // erase element number i (order in list is not preserved)
    void remove_unordered( int i ) {
        if ( i + 1 != _size )
            _data[ i ] = back();
        pop_back();
    }

    T *begin() { return _data;              }
    T *end  () { return _data + _size;      }
    T *ptr  () { return _data;              }
    T &back () { return _data[ _size - 1 ]; }

    const T *begin() const { return _data;              }
    const T *end  () const { return _data + _size;      }
    const T *ptr  () const { return _data;              }
    const T &back () const { return _data[ _size - 1 ]; }

private:
    void _mv_data_for_size( S wanted ) { // no check if reservation if necessary or not (size < old_size, ...)
        _rese = wanted;
        // -> TODO use of realloc
        T_ *old_data = _data;
        _data = _alloc( _rese );
        for(S i=0;i<_size;++i)
            new( _data + i ) T_( old_data[ i ] );
        for(S i=_size-1;i>=0;--i)
            old_data[ i ].~T_();
        _free( old_data );
    }

    void _free( T *ptr ) {
        if ( ptr != reinterpret_cast<T *>( _prer ) )
            free( ptr );
    }

    T *_alloc( int nsi ) {
        if ( nsi <= static_prer_ )
            return reinterpret_cast<T *>( _prer );
        if ( alignment > 1 )
            return reinterpret_cast<T *>( memalign( max( 8, (int)sizeof( T ) * alignment ), sizeof( T ) * nsi ) );
        return reinterpret_cast<T *>( malloc( sizeof( T ) * nsi ) );
    }

    C  _prer[ sizeof( T ) * static_prer_ ];
    S  _size;
    S  _rese;
    T *_data;
    bool owning;
};



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
*/
template<class T,int s,int p,int a>
class BasicVec : public VecAncestor<T,s,p,a> {
public:
    typedef VecAncestor<T,s,p,a> VA;

    BasicVec() {}
    template<class T0> BasicVec( const T0 &v0 ) : VA( v0 ) {}
    template<class T0,class T1> BasicVec( const T0 &v0, const T1 &v1 ) : VA( v0, v1 ) {}
    template<class T0,class T1,class T2> BasicVec( const T0 &v0, const T1 &v1, const T2 &v2 ) : VA( v0, v1, v2 ) {}

    BasicVec &operator=( const BasicVec &v ) { VA::operator=( v ); return *this; }

    template<class T2,int s2,int p2>
    BasicVec &operator=( const BasicVec<T2,s2,p2> &v ) { VA::operator=( v ); return *this; }

    template<class T2>
    bool contains( const T2 &d ) const {
        for(int i=0;i<VA::size();++i)
            if ( VA::operator[]( i ) == d )
                return true;
        return false;
    }

    template<class ValItem> void apply( const ValItem &op ) const { for(int j=0;j<VA::size();++j) op( VA::operator[]( j ) ); }
    template<class ValItem> void apply(       ValItem &op ) const { for(int j=0;j<VA::size();++j) op( VA::operator[]( j ) ); }
    template<class ValItem> void apply( const ValItem &op )       { for(int j=0;j<VA::size();++j) op( VA::operator[]( j ) ); }
    template<class ValItem> void apply(       ValItem &op )       { for(int j=0;j<VA::size();++j) op( VA::operator[]( j ) ); }

    void write_to_stream( Stream &os ) const {
        WriteToStream ws( os );
        apply( ws );
    }

    void set( const T &val ) {
        for(int i=0;i<VA::size();++i)
            VA::operator[]( i ) = val;
    }

    template<class T2,int s2,int p2>
    bool operator==( const BasicVec<T2,s2,p2> &vec ) const {
        if ( VA::size() != vec.size() )
            return false;
        for(int i=0;i<VA::size();++i)
            if ( VA::operator[]( i ) != vec[ i ] )
                return false;
        return true;
    }
};

} // namespace Metil

#endif // METIL_VEC_H
