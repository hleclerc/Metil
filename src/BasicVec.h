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

#ifndef METIL_VEC_H
#define METIL_VEC_H

#include "Malloc.h"
#include "Assert.h"
#include "TensorOrder.h"
#include "EnableIf.h"

BEG_METIL_NAMESPACE;

template<class T,int s=-1,int p=0>
class BasicVec;

template<class T,int s,int p>
struct TensorOrder<BasicVec<T,s,p> > {
    static const int res = 1;
};

/**
  @brief Simple vector, generic type, static or dynamic size, possible "prereservation", contiguous data

  Examples :
   - BasicVec<double> -> dynamic vector of doubles.
   - BasicVec<double,3> -> static vector of doubles, size 3.
   - BasicVec<double,0> -> static vector of doubles, size 0.
   - BasicVec<double,-1> -> dynamic vector. Size begins at 0.
   - BasicVec<double,-1,4> -> dynamic vector with reservation "on stack" of size 4 : if size remains <= 4, no malloc are necessary. Size begins at 0.

*/
template<class ItemType,int _static_size,int static_rese>
class BasicVec {
public:
    typedef ItemType T;
    typedef ST S;
    static const int static_size = _static_size;
    static const int static_prer = static_rese;

    __inline__ BasicVec() {}

    template<class T0>
    __inline__ void _init_using_1_arg( const T0 &v0, Number<0> ) {
        for(int i=0;i<static_size;++i)
            _data[ i ] = v0;
    }

    template<class T0>
    __inline__ void _init_using_1_arg( const T0 &v0, Number<1> ) {
        ASSERT_IF_DEBUG( v0.size() == static_size_ );
        for(int i=0;i<static_size;++i)
            _data[ i ] = v0[ i ];
    }

    template<class T0>
    __inline__ BasicVec( const T0 &v0 ) {
        _init_using_1_arg( v0, Number<TensorOrder<T0>::res>() );
    }

    template<class T0,class T1>
    __inline__ BasicVec( const T0 &v0, const T1 &v1 ) {
        ASSERT_IF_DEBUG( static_size_ == 2 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
    }

    template<class T0,class T1,class T2>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2 ) {
        ASSERT_IF_DEBUG( static_size_ == 3 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
    }

    template<class T0,class T1,class T2,class T3>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3 ) {
        ASSERT_IF_DEBUG( static_size_ == 4 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
    }

    template<class T0,class T1,class T2,class T3,class T4>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4 ) {
        ASSERT_IF_DEBUG( static_size_ == 5 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 ) {
        ASSERT_IF_DEBUG( static_size_ == 6 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5,class T6>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 , const T6 &v6) {
        ASSERT_IF_DEBUG( static_size_ == 7 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
        _data[ 6 ] = v6;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5,class T6,class T7>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 , const T6 &v6, const T7 &v7) {
        ASSERT_IF_DEBUG( static_size_ == 8 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
        _data[ 6 ] = v6;
        _data[ 7 ] = v7;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 , const T6 &v6, const T7 &v7, const T8 &v8) {
        ASSERT_IF_DEBUG( static_size_ == 9 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
        _data[ 6 ] = v6;
        _data[ 7 ] = v7;
        _data[ 8 ] = v8;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 , const T6 &v6, const T7 &v7, const T8 &v8, const T9 &v9) {
        ASSERT_IF_DEBUG( static_size_ == 10 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
        _data[ 6 ] = v6;
        _data[ 7 ] = v7;
        _data[ 8 ] = v8;
        _data[ 9 ] = v9;
    }

    template<class T0,class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
    __inline__ BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4, const T5 &v5 , const T6 &v6, const T7 &v7, const T8 &v8, const T9 &v9, const T10 &v10) {
        ASSERT_IF_DEBUG( static_size_ == 11 );
        _data[ 0 ] = v0;
        _data[ 1 ] = v1;
        _data[ 2 ] = v2;
        _data[ 3 ] = v3;
        _data[ 4 ] = v4;
        _data[ 5 ] = v5;
        _data[ 6 ] = v6;
        _data[ 7 ] = v7;
        _data[ 8 ] = v8;
        _data[ 9 ] = v9;
        _data[ 10 ] = v10;
    }

    __inline__ BasicVec( Size, int s ) {
        ASSERT_IF_DEBUG( s == static_size );
    }

    template<class T0>
    __inline__ BasicVec( Size, int s, const T0 &v0 ) {
        ASSERT_IF_DEBUG( s == static_size );
        for(int i=0;i<static_size;++i)
            _data[ i ] = v0;
    }

    __inline__ BasicVec( const BasicVec &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(int i=0;i<static_size;++i)
            _data[ i ] = v[ i ];
    }

    __inline__ void operator=( const BasicVec &v ) {
        ASSERT_IF_DEBUG( static_size_ == v.size() );
        for(int i=0;i<static_size;++i)
            _data[ i ] = v[ i ];
    }

    template<class T0>
    __inline__ void operator=( const T0 &v0 ) {
        _init_using_1_arg( v0, Number<TensorOrder<T0>::res>() );
    }

    __inline__ void set( T val ) {
        for( ST i = 0; i < static_size; ++i )
            _data[ i ] = val;
    }

    __inline__ void operator+=( const BasicVec &v ) {
        for( int i = 0; i < static_size; ++i )
            _data[ i ] += v[ i ];
    }

    __inline__ int size() const {
        return static_size;
    }

    __inline__ int rese() const {
        return static_size;
    }

    __inline__ const T &operator[]( int i ) const {
        ASSERT_IF_DEBUG( i < static_size );
        return _data[ i ];
    }

    __inline__ T &operator[]( int i ) {
        ASSERT_IF_DEBUG( i < static_size );
        return _data[ i ];
    }

    __inline__ bool empty() const { return size() == 0; }

    __inline__ void resize( int new_size ) {
        ASSERT_IF_DEBUG( new_size == static_size_ );
    }

    __inline__ void resize( int new_size, const T &val ) {
        ASSERT_IF_DEBUG( new_size == static_size_ );
    }

    __inline__ void reserve( int new_rese ) {
        ASSERT_IF_DEBUG( new_rese == static_size_ );
    }

    __inline__ T *begin() { return _data; }
    __inline__ T *end() { return _data + static_size; }
    __inline__ const T *begin() const { return _data; }
    __inline__ const T *end() const { return _data + static_size; }

    __inline__ T *ptr() { return _data; }
    __inline__ const T *ptr() const { return _data; }

    __inline__ T &back() { return _data[ static_size - 1 ]; }
    __inline__ const T &back() const { return _data[ static_size - 1 ]; }

    template<class T2>
    __inline__ bool contains( const T2 &d ) const {
        for(int i=0;i<static_size;++i)
            if ( _data[ i ] == d )
                return true;
            return false;
    }

    __inline__ bool operator==( const BasicVec &v ) const {
        for(int i=0;i<static_size;++i)
            if ( _data[ i ] != v[ i ] )
                return false;
            return true;
    }

    __inline__ bool operator==( const T &v ) const {
        for(int i=0;i<static_size;++i)
            if ( _data[ i ] != v )
                return false;
            return true;
    }


    __inline__ BasicVec operator+( const BasicVec &vec ) const {
        BasicVec res;
        for(int i=0;i<static_size;++i)
            res[ i ] = operator[]( i ) + vec[ i ];
        return res;
    }

    template<class TS>
    void write_str( TS &os ) const {
        if ( size() ) {
            os << operator[]( 0 );
            for(ST i=1;i<size();++i) {
                os.write_separator( 0 );
                os <<  operator[]( i );
            }
        }
    }
private:
    T _data[ static_size ];
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

// dynamic case
template<class T_,int static_prer_>
class BasicVec<T_,-1,static_prer_> {
public:
    typedef T_ T;
    static const ST static_size = -1;
    static const ST static_prer = static_prer_;

    BasicVec() : _size( 0 ), _rese( static_prer_ ), _data( (T_ *)_prer ) {}

    BasicVec( const T &v0 ) : _size( 1 ), _rese( 1 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
    }

    template<class T0>
    BasicVec( const T0 &v0, typename EnableIf<TensorOrder<T0>::res==0,Nawak>::T = Nawak() ) : _size( 1 ), _rese( 1 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
    }

    template<class T0,class T1>
    BasicVec( const T0 &v0, const T1 &v1 ) : _size( 2 ), _rese( 2 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
    }

    template<class T0,class T1,class T2>
    BasicVec( const T0 &v0, const T1 &v1, const T2 &v2 ) : _size( 3 ), _rese( 3 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
        new( _data + 2 ) T_( v2 );
    }

    template<class T0,class T1,class T2,class T3>
    BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3 ) : _size( 4 ), _rese( 4 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
        new( _data + 2 ) T_( v2 );
        new( _data + 3 ) T_( v3 );
    }

    template<class T0,class T1,class T2,class T3,class T4>
    BasicVec( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3, const T4 &v4 ) : _size( 5 ), _rese( 5 * sizeof( T ) ), _data( _alloc() ) {
        new( _data + 0 ) T_( v0 );
        new( _data + 1 ) T_( v1 );
        new( _data + 2 ) T_( v2 );
        new( _data + 3 ) T_( v3 );
        new( _data + 4 ) T_( v4 );
    }

    template<class S>
    BasicVec( Size, S s ) : _size( s ), _rese( s * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<s;++i)
            new( _data + i ) T_;
    }

    template<class S>
    BasicVec( Size, S s, T *ptr ) : _size( s ), _rese( s * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<s;++i)
            new( _data + i ) T_( ptr[ i ] );
    }

    template<class S,class T0>
    BasicVec( Size, S s, const T0 &v0 ) : _size( s ), _rese( s * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<s;++i)
            new( _data + i ) T_( v0 );
    }

    template<class S,class T0,class T1>
    BasicVec( Size, S s, const T0 &v0, const T1 &v1 ) : _size( s ), _rese( s * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<s;++i)
            new( _data + i ) T_( v0, v1 );
    }

    template<class S>
    BasicVec( Rese, S s ) : _size( 0 ), _rese( s * sizeof( T ) ), _data( _alloc() ) {
    }


    BasicVec( const BasicVec &v ) : _size( v.size() ), _rese( _size * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<_size;++i)
            new( _data + i ) T_( v[ i ] );
    }

    template<class T2,int s,int p>
    BasicVec( const BasicVec<T2,s,p> &v ) : _size( v.size() ), _rese( _size * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<_size;++i)
            new( _data + i ) T_( v[ i ] );
    }

    BasicVec( T_ *beg, T_ *end ) : _size( end - beg ), _rese( _size * sizeof( T ) ), _data( _alloc() ) {
        for(ST i=0;i<_size;++i)
            new( _data + i ) T_( beg[ i ] );
    }

    void operator=( const BasicVec &v ) {
        reserve( v._size );
        for(ST i=_size-1;i>=v._size;--i) // destruction for i > v._size
            _data[ i ].~T();
        for(ST i=0;i<_size and i < v._size;++i) // operator= for i < both
            _data[ i ] = v._data[ i ];
        for(ST i=_size;i<v._size;++i) // placement new
            new( _data + i ) T_( v._data[ i ] );
        _size = v._size;
    }

    template<class T2,int s,int p>
    void operator=( const BasicVec<T2,s,p> &v ) {
        reserve( v.size() );
        for(ST i=_size-1;i>=v.size();--i) // destruction for i >= v._size
            _data[ i ].~T();
        for(ST i=0;i<(_size<v.size()?_size:v.size());++i) // operator= for i < both
            _data[ i ] = v[ i ];
        for(ST i=_size;i<v.size();++i) // placement new
            new( _data + i ) T_( v[ i ] );
        _size = v.size();
    }

    ~BasicVec() {
        for(ST i=_size-1;i>=0;--i)
            _data[ i ].~T_();
        __free( _data, _rese );
    }

    __inline__ void set( T val ) {
        for( ST i = 0; i < _size; ++i )
            _data[ i ] = val;
    }

    __inline__ const T &operator[]( ST i ) const { ASSERT_IF_DEBUG( i < _size ); return _data[ i ]; }
    __inline__ T &operator[]( ST i ) { ASSERT_IF_DEBUG( i < _size ); return _data[ i ]; }

    __inline__ ST size() const { return _size; }

    __inline__ bool empty() const { return size() == 0; }

    template<class T2>
    BasicVec &operator<<( const T2 &val ) {
        push_back( val );
        return *this;
    }

    T *push_back() {
        reserve_wm( _size + 1 );
        new( _data + _size ) T_;
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

    template<class T0,class T1,class T2,class T3>
    T *push_back( const T0 &v0, const T1 &v1, const T2 &v2, const T3 &v3 ) {
        reserve_wm( _size + 1 );
        new( _data + _size ) T_( v0, v1, v2, v3 );
        return _data + _size++;
    }

    void reserve_wm( ST wanted ) { // if not enough, reserve more than wanted...
        wanted *= sizeof( T_ );
        if ( wanted <= _rese )
            return;
        ST n = 2 * ( _rese + 1 );
        _mv_data_for_size( wanted > n ? wanted : n );
    }

    void reserve( ST wanted ) {
        wanted *= sizeof( T_ );
        if ( wanted <= _rese )
            return;
        _mv_data_for_size( wanted );
    }

    ST rese() const { return _rese / sizeof( T_ ); }

    void resize( ST new_size ) {
        for(ST i=_size-1;i>=new_size;--i)
            _data[ i ].~T();
        //
        reserve( new_size );
        for(ST i=_size;i<new_size;++i)
            new( _data + i ) T;
        //
        _size = new_size;
    }

    template<class T0>
    void resize( ST new_size, const T0 &v0 ) {
        for(ST i=_size-1;i>=new_size;--i)
            _data[ i ].~T();
        //
        reserve( new_size );
        for(ST i=_size;i<new_size;++i)
            new( _data + i ) T( v0 );
        //
        _size = new_size;
    }

    template<class T0,class T1>
    void resize( ST new_size, const T0 &v0, const T1 &v1 ) {
        for(ST i=_size-1;i>=new_size;--i)
            _data[ i ].~T();
        //
        reserve( new_size );
        for(ST i=_size;i<new_size;++i)
            new( _data + i ) T( v0, v1 );
        //
        _size = new_size;
    }

    T &pop_back() {
        _data[ --_size ].~T();
        return _data[ _size ];
    }

    // append val if not present and return pointer to new elem. Else, return pointer to elem which is equal to val
    template<class T2>
    T *push_back_unique( const T2 &val ) {
        for(ST i=0;i<_size;++i)
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
        for(ST i=0;i<_size;++i) {
            if ( _data[ i ] == val ) {
                remove_unordered( i );
                return;
            }
        }
    }

    // erase first element equal to val
    void remove_first( const T &val ) {
        for(ST i=0;i<_size;++i) {
            if ( _data[ i ] == val ) {
                remove( i );
                return;
            }
        }
    }

    // erase element number i (order in list is not preserved)
    void remove_unordered( ST i ) {
        if ( i + 1 != _size )
            _data[ i ] = back();
        pop_back();
    }

    // erase element number i
    void remove( ST i ) {
        for(ST j=i;j<_size - 1;++j)
            operator[]( j ) = operator[]( j + 1 );
        pop_back();
    }

    template<class Hdf,class TS>
    void write_to( Hdf &hdf, const TS &name ) {
        BasicVec<int,1> s( size() );
        hdf.write( name, ptr(), s );
    }
    
    template<class Hdf,class TS>
    void write_to( Hdf &hdf, const TS &name , BasicVec<TS> &tags, BasicVec<TS> &tags_value) {
        BasicVec<int,1> s( size() );
        hdf.write( name, ptr(), s , tags, tags_value);
    }
    

    template<class Hdf,class TS>
    void read_from( const Hdf &hdf, const TS &name ) {
        // size
        BasicVec<int,1> s;
        hdf.read_size( name, s );
        resize( s[ 0 ] );
        // data
        hdf.read_data( name, ptr(), s, s );
    }
    
    template<class Hdf,class TS>
    void read_from( const Hdf &hdf, const TS &name , BasicVec<TS> &tags, BasicVec<TS> &tags_value) {
        // size
        BasicVec<int,1> s;
        hdf.read_size( name, s );
        resize( s[ 0 ] );
        // data
        hdf.read_data( name, ptr(), s, s, tags, tags_value );
    }

    T *begin() { return _data;              }
    T *end  () { return _data + _size;      }
    T *ptr  () { return _data;              }
    T &back () { return _data[ _size - 1 ]; }

    const T *begin() const { return _data;              }
    const T *end  () const { return _data + _size;      }
    const T *ptr  () const { return _data;              }
    const T &back () const { return _data[ _size - 1 ]; }

    template<class T2>
    bool contains( const T2 &d ) const {
        for(int i=0;i<_size;++i)
            if ( _data[ i ] == d )
                return true;
        return false;
    }

    template<class T2>
    int first_index_equal_to( const T2 &d ) const { /// returns -1 if not found
        for(int i=0;i<_size;++i)
            if ( _data[ i ] == d )
                return i;
        return -1;
    }

    bool operator==( const BasicVec &v ) const {
        for(int i=0;i<_size;++i)
            if ( _data[ i ] != v[ i ] )
                return false;
        return true;
    }

    bool operator==( const T &v ) const {
        for(int i=0;i<_size;++i)
            if ( _data[ i ] != v )
                return false;
            return true;
    }

    bool operator!=( const T &v ) const {
        for(int i=0;i<_size;++i)
            if ( _data[ i ] != v )
                return true;
            return false;
    }

    BasicVec operator+( const BasicVec &vec ) const {
        BasicVec res( Size(), ( size() < vec.size() ? size() : vec.size() ) );
        for(int i=0;i<res.size();++i)
            res[ i ] = operator[]( i ) + vec[ i ];
        return res;
    }

    BasicVec left_to( ST end ) const {
        BasicVec res( Rese(), end );
        for(int i=0;i<end;++i)
            res << operator[]( i );
        return res;
    }

    template<class TT>
    void insert( ST pos, const TT &val ) {
        if ( size() ) {
            TT last = back();
            push_back( last );
            for( ST i = size() - 3; i >= pos; --i )
                operator[]( i + 1 ) = operator[]( i );
            operator[]( pos ) = val;
        } else {
            push_back( val );
        }
    }

    template<class T2>
    void replace( const T2 &a, const T2 &b ) { ///< replace a by b
        for(int i=0;i<size();++i)
            if ( operator[]( i ) == a )
                operator[]( i ) = b;
    }

    template<class TS>
    void write_str( TS &os ) const {
        if ( size() ) {
            os << operator[]( 0 );
            for(ST i=1;i<size();++i) {
                os.write_separator( 0 );
                os <<  operator[]( i );
            }
        }
    }

private:
    void __free( T *ptr, ST rese ) {
        if ( ptr != reinterpret_cast<T *>( _prer ) )
            FREE( ptr, rese );
    }

    void _mv_data_for_size( ST wanted_in_bytes ) { // no check if reservation if necessary or not (size < old_size, ...)
        // -> TODO use of realloc
        T_ *old_data = _data;
        ST old_rese = _rese;
        _rese = wanted_in_bytes;
        _data = _alloc();
        for( ST i = 0; i < _size; ++i )
            new( _data + i ) T_( old_data[ i ] );
        for( ST i = _size - 1; i >= 0; --i )
            old_data[ i ].~T_();
        __free( old_data, old_rese );
    }

    T *_alloc() { // use and update _rese
        if ( _rese <= ST( static_prer_ * sizeof( T ) ) ) {
            _rese = ST( static_prer_ * sizeof( T ) );
            return reinterpret_cast<T *>( _prer );
        }
        return reinterpret_cast<T *>( MALLOC( _rese ) );
    }

    char _prer[ static_prer_ * sizeof( T ) ];
    ST   _size; // number of item (type T)
    ST   _rese; // number of bytes
    T   *_data;
};

template<class T> BasicVec<T,1> svec( const T &a ) { return BasicVec<T,1>( a ); }
template<class T> BasicVec<T,2> svec( const T &a, const T &b ) { return BasicVec<T,2>( a, b ); }
template<class T> BasicVec<T,3> svec( const T &a, const T &b, const T &c ) { return BasicVec<T,3>( a, b, c ); }
template<class T> BasicVec<T,4> svec( const T &a, const T &b, const T &c, const T &d ) { return BasicVec<T,4>( a, b, c, d ); }

template<class T> BasicVec<T> dvec( const T &a ) { return BasicVec<T>( a ); }
template<class T> BasicVec<T> dvec( const T &a, const T &b ) { return BasicVec<T>( a, b ); }
template<class T> BasicVec<T> dvec( const T &a, const T &b, const T &c ) { return BasicVec<T>( a, b, c ); }
template<class T> BasicVec<T> dvec( const T &a, const T &b, const T &c, const T &d ) { return BasicVec<T>( a, b, c, d ); }

template<class TV>
__inline__ bool all( const TV &vec ) {
    for(ST i=0;i<vec.size();++i)
        if ( not vec[ i ] )
            return false;
    return true;
}

template<class TV>
__inline__ bool any( const TV &vec ) {
    for(ST i=0;i<vec.size();++i)
        if ( vec[ i ] )
            return true;
    return false;
}

template<class T_,int s_,int p_,class T2>
__inline__ BasicVec<bool,s_,p_> operator>=( const BasicVec<T_,s_,p_> &a, const T2 &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] >= b;
    return res;
}

template<class T_,int s_,int p_,class T2>
__inline__ BasicVec<bool,s_,p_> operator<( const BasicVec<T_,s_,p_> &a, const T2 &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] < b;
    return res;
}

template<class T_,int s_,int p_,class T2,int s2,int p2>
__inline__ BasicVec<bool,s_,p_> operator<( const BasicVec<T_,s_,p_> &a, const BasicVec<T2,s2,p2> &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] < b[ i ];
    return res;
}

template<class T_,int s_,int p_,class T2,int s2,int p2>
__inline__ BasicVec<bool,s_,p_> operator>=( const BasicVec<T_,s_,p_> &a, const BasicVec<T2,s2,p2> &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] >= b[ i ];
    return res;
}

template<class T_,int s_,int p_,class T2,int s2,int p2>
__inline__ BasicVec<bool,s_,p_> operator!=( const BasicVec<T_,s_,p_> &a, const BasicVec<T2,s2,p2> &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] != b[ i ];
    return res;
}

template<class T_,int s_,int p_,class T2,int s2,int p2>
__inline__ BasicVec<bool,s_,p_> operator==( const BasicVec<T_,s_,p_> &a, const BasicVec<T2,s2,p2> &b ) {
    BasicVec<bool,s_,p_> res( Size(), a.size() );
    for(ST i = 0; i < a.size(); ++i )
        res[ i ] = a[ i ] == b[ i ];
    return res;
}

///
template<class T>
__inline__ void make_vec_from_xyz_struct( BasicVec<int,1> &vec, const T &val ) { vec[ 0 ] = val.x; }

template<class T>
__inline__ void make_vec_from_xyz_struct( BasicVec<int,2> &vec, const T &val ) { vec[ 0 ] = val.x; vec[ 1 ] = val.y; }

template<class T>
__inline__ void make_vec_from_xyz_struct( BasicVec<int,3> &vec, const T &val ) { vec[ 0 ] = val.x; vec[ 1 ] = val.y; vec[ 2 ] = val.z; }

END_METIL_NAMESPACE

#endif // METIL_VEC_H
