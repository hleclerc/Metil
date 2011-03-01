#ifndef STATICBASICVEC_H
#define STATICBASICVEC_H

#ifndef ASSERT_IF_DEBUG
    #define ASSERT_IF_DEBUG( A )
#endif // DEBUG

#ifndef __inline__
    #define __inline__ __device__ __host__ inline
#endif // __inline__


template<class T,int s=-1,int p=0>
class BasicVec;

template<class T,int s,int p>
struct TensorOrder<BasicVec<T,s,p> > {
    static const int res = 1;
};

/*
  if static_size == 0
*/
template<class ItemType,int static_rese>
class BasicVec<ItemType,0,static_rese> {
public:
    typedef ItemType T;
    typedef int S;
    static const int static_size = 0;
    static const int static_prer = static_rese;

    __inline__ const T &operator[]( int i ) const { ASSERT_IF_DEBUG( 0 ); return *dummy(); }
    __inline__ T &operator[]( int i ) { ASSERT_IF_DEBUG( 0 ); return *dummy(); }
    __inline__ S size() const { return 0; }

    __inline__ T *dummy() const { return 0; }
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
    typedef int S;
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

#endif // STATICBASICVEC_H
