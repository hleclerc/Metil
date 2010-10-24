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

#ifndef METIL_MAT_H
#define METIL_MAT_H

#include "BasicVec.h"
#include "MatStdStructuresAndStorages.h"

namespace Metil {


/**
    BasicMat<double> -> dynamic matrix of doubles
*/
template<class T_,class Structure_=Gen<>,class Storage_=Dense<> >
class Mat;

///
template<class TM>
void write_mat_to_stream( const TM &m, Stream &os ) {
    for(int i=0;i<m.nb_rows();++i) {
        for(int j=0;j<m.nb_cols();++j)
            os << ( j ? " " : "" ) << m( i, j );
        os << "\n";
    }
}


/**
    Specialization Gen Dense static -> tiny matrices (data is not aligned)
*/
template<class T_,int sr,int sc,int p>
class BasicMat<T_,Gen<sr,sc,p>,Dense<> > {
public:
    typedef T_ T;
    typedef int S;
    static const int static_data_size = sr * sc;
    
    Mat() {}
    
    Mat( const Mat &v ) { for(int i=0;i<static_data_size;++i) _data[ i ] = v._data[ i ]; }
    
    template<class T2>
    Mat( const T2 &val ) { for(int i=0;i<static_data_size;++i) _data[ i ] = val; }
    
    Mat( SetSize, int nb_rows, int nb_cols ) { ASSERT_IF_DEBUG( nb_rows == sr ); ASSERT_IF_DEBUG( nb_rows == sc ); }
    
    template<class T2>
    Mat( SetSize, int nb_rows, int nb_cols, const T2 &val ) { ASSERT_IF_DEBUG( nb_rows == sr ); ASSERT_IF_DEBUG( nb_rows == sc ); for(int i=0;i<static_data_size;++i) _data[ i ] = val; }
    
    Mat &operator=( const Mat &v ) { _data = v._data; return *this; }

    S nb_rows() const { return sr; }
    S nb_cols() const { return sr; }
    
    const T &operator()( int i, int j ) const {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        return _data[ sc * i + j ];
    }
    
    T &operator()( int i, int j ) {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        return _data[ sc * i + j ];
    }

    void set( const T &val ) { for(int i=0;i<static_data_size;++i) _data[ i ] = val; }
    
    void resize( int nb_rows, int nb_cols ) { ASSERT_IF_DEBUG( nb_rows == sr ); ASSERT_IF_DEBUG( nb_cols == sc ); }
    
    T *ptr() { return _data; }
    const T *ptr() const { return _data; }
    
    void write_to_stream( Stream &os ) const { write_mat_to_stream( *this, os ); }
    
private:
    T_ _data[ static_data_size ];
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
    Specialization Gen Dense dynamic
*/
template<class T_,int p>
class BasicMat<T_,Gen<-1,-1,p>,Dense<> > {
public:
    typedef T_ T;
    typedef int S;
    static const int alignment = SimdAlignment<T>::res;
    
    Mat() : _nb_rows( 0 ), _nb_cols( 0 ), _in_rows( 0 ), _in_cols( 0 ), _data( const_cast<T *>( reinterpret_cast<const T *>( _prer ) ) ), owning( true ) {}
    
    Mat( const Mat &v ) : _nb_rows( v._nb_rows ), _nb_cols( v._nb_cols ), _in_rows( v._in_rows ), _in_cols( v._in_cols ), _data( _alloc( v._in_rows * v._in_cols ) ), owning( true ) {
        for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
            for(int c=0;c<_nb_cols;++c,++i)
                new( _data + i ) T( v._data[ i ] );
    }
    
    Mat( SetSize, int nb_rows, int nb_cols ) : _nb_rows( nb_rows ), _nb_cols( nb_cols ), _in_rows( nb_rows ), _in_cols( alignment > 1 ? ceil( nb_cols, alignment ) : nb_cols ), _data( _alloc( _in_rows * _in_cols ) ), owning( true ) {
        for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
            for(int c=0;c<_nb_cols;++c,++i)
                new( _data + i ) T;
    }
    
    template<class T0>
    Mat( SetSize, int nb_rows, int nb_cols, const T0 &v0 ) : _nb_rows( nb_rows ), _nb_cols( nb_cols ), _in_rows( nb_rows ), _in_cols( alignment > 1 ? ceil( nb_cols, alignment ) : nb_cols ), _data( _alloc( _in_rows * _in_cols ) ), owning( true ) {
        for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
            for(int c=0;c<_nb_cols;++c,++i)
                new( _data + i ) T( v0 );
    }
    
    Mat &operator=( const Mat &v ) {
        owning = true;
        if ( _nb_rows == v._nb_rows and _nb_cols == v._nb_cols and _in_rows == v._in_rows and _in_cols == v._in_cols ) {
            for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
                for(int c=0;c<_nb_cols;++c,++i)
                    _data[ i ] = v._data[ i ];
        } else  {
            // delete old data
            for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
                for(int c=0;c<_nb_cols;++c,++i)
                    _data[ i ].~T();
            //
            if ( _in_rows * _in_cols < v._in_rows * v._in_cols ) {
                _free( _data );
                _data = _alloc( v._in_rows * v._in_cols );
            }
            for(int r=0,i=0;r<v._nb_rows;++r,i+=v._in_cols-v._nb_cols)
                for(int c=0;c<v._nb_cols;++c,++i)
                    new( _data + i ) T( v._data[ i ] );
            _nb_rows = v._nb_rows;
            _nb_cols = v._nb_cols;
            _in_rows = v._in_rows;
            _in_cols = v._in_cols;
        }
        return *this;
    }

    ~Mat() {
        if ( owning ) {
            for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
                for(int c=0;c<_nb_cols;++c,++i)
                    _data[ i ].~T();
            _free( _data );
        }
    }
    
    S nb_rows() const { return _nb_rows; }
    S nb_cols() const { return _nb_cols; }
    
    const T &operator()( int i, int j ) const {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        return _data[ _in_cols * i + j ];
    }
    
    T &operator()( int i, int j ) {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        return _data[ _in_cols * i + j ];
    }
    
    void set( const T &val ) {
        for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
            for(int c=0;c<_nb_cols;++c,++i)
                _data[ i ] = val;
    }

    void resize( int new_nb_rows, int new_nb_cols ) {
        if ( new_nb_rows > _in_rows or new_nb_cols > _in_cols ) {
            T *old_data = _data;
            int new_in_rows = new_nb_rows;
            int new_in_cols = ceil( new_nb_cols, alignment );
            _data = _alloc( new_in_cols * new_in_rows );
            //
            for(int r=0,o=0;r<min(_nb_rows,new_nb_rows);++r, o += _in_cols )
                for(int c=0;c<min(_nb_cols,new_nb_cols);++c)
                    new( _data + r * new_in_cols + c ) T( old_data[ o + c ] );
            for(int r=_nb_rows;r<new_nb_rows;++r)
                for(int c=0;c<min(_nb_cols,new_nb_cols);++c)
                    new( _data + r * new_in_cols + c ) T;
            for(int r=0;r<min(_nb_rows,new_nb_rows);++r)
                for(int c=_nb_cols;c<new_nb_cols;++c)
                    new( _data + r * new_in_cols + c ) T;
            for(int r=_nb_rows;r<new_nb_rows;++r)
                for(int c=_nb_cols;c<new_nb_cols;++c)
                    new( _data + r * new_in_cols + c ) T;

            if ( owning ) {
                for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
                    for(int c=0;c<_nb_cols;++c,++i)
                        old_data[ i ].~T();
                _free( old_data );
            }
            owning = true;

            _in_rows = new_in_rows;
            _in_cols = new_in_cols;
        }
        _nb_rows = new_nb_rows;
        _nb_cols = new_nb_cols;
    }

    template<class T2>
    void resize( int new_nb_rows, int new_nb_cols, const T2 &val ) {
        if ( new_nb_rows > _in_rows or new_nb_cols > _in_cols ) {
            T *old_data = _data;
            int new_in_rows = new_nb_rows;
            int new_in_cols = ceil( new_nb_cols, alignment );
            _data = _alloc( new_in_cols * new_in_rows );
            //
            for(int r=0,o=0;r<min(_nb_rows,new_nb_rows);++r, o += _in_cols )
                for(int c=0;c<min(_nb_cols,new_nb_cols);++c)
                    new( _data + r * new_in_cols + c ) T( old_data[ o + c ] );
            for(int r=_nb_rows;r<new_nb_rows;++r)
                for(int c=0;c<min(_nb_cols,new_nb_cols);++c)
                    new( _data + r * new_in_cols + c ) T( val );
            for(int r=0;r<min(_nb_rows,new_nb_rows);++r)
                for(int c=_nb_cols;c<new_nb_cols;++c)
                    new( _data + r * new_in_cols + c ) T( val );
            for(int r=_nb_rows;r<new_nb_rows;++r)
                for(int c=_nb_cols;c<new_nb_cols;++c)
                    new( _data + r * new_in_cols + c ) T( val );

            if ( owning ) {
                for(int r=0,i=0;r<_nb_rows;++r,i+=_in_cols-_nb_cols)
                    for(int c=0;c<_nb_cols;++c,++i)
                        old_data[ i ].~T();
                _free( old_data );
            }
            owning = true;

            _in_rows = new_in_rows;
            _in_cols = new_in_cols;
        }
        _nb_rows = new_nb_rows;
        _nb_cols = new_nb_cols;
    }

    T *ptr() { return _data.ptr(); }
    const T *ptr() const { return _data.ptr(); }
    
    void write_to_stream( Stream &os ) const { write_mat_to_stream( *this, os ); }
    
private:
    void _free( T *ptr ) {
        if ( ptr != const_cast<T *>( reinterpret_cast<const T *>( _prer ) ) )
            free( ptr );
    }
    
    T *_alloc( int nsi ) {
        if ( nsi <= p )
            return const_cast<T *>( reinterpret_cast<const T *>( _prer ) );
        if ( alignment > 1 ) {
            void *res = memalign( max( 8, (int)sizeof( T ) * alignment ), sizeof( T ) * nsi );
            // if ( allocated )
            //     throw "Not enough room...";
            return reinterpret_cast<T *>( res );
        }
        return reinterpret_cast<T *>( malloc( sizeof( T ) * nsi ) );
    }
    
    char *_prer[ sizeof( T ) * p ]; // reserved room in stack
    S _nb_rows; // user number of rows
    S _nb_cols; // user number of cols
    S _in_rows; // internal number of rows (for storage)
    S _in_cols; // internal number of cols (for storage)
    T *_data;
    bool owning;
};


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
    Specialization Sym Dense static
*/
template<class T_,int s,int p>
class BasicMat<T_,Sym<s,p>,Dense<> > {
public:
    typedef T_ T;
    typedef int S;
    static const int nb_terms = s * ( s + 1 ) / 2;

    Mat() {}

    Mat( const Mat &v ) {
        for(int i=0;i<nb_terms;++i)
            _data[ i ] = v._data[ i ];
    }

    Mat( SetSize, int nb_rows, int nb_cols = 0 ) {
        ASSERT_IF_DEBUG( nb_cols == s or nb_rows == s );
    }

    template<class T0>
    Mat( SetSize, int nb_rows, int nb_cols, const T0 &v0 ) {
        ASSERT_IF_DEBUG( nb_cols == s or nb_rows == s );
        for(int i=0;i<nb_terms;++i)
            _data[ i ] = v0;
    }

    Mat &operator=( const Mat &v ) {
        for(int i=0;i<nb_terms;++i)
            _data[ i ] = v._data[ i ];
        return *this;
    }

    S nb_rows() const { return s; }
    S nb_cols() const { return s; }

    const T &operator()( int i, int j ) const {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i <  s );
        ASSERT_IF_DEBUG( j <  s );
        if ( i < j )
            swap( i, j );
        return _data[ i * ( i + 1 ) / 2 + j ];
    }

    T &operator()( int i, int j ) {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i <  s );
        ASSERT_IF_DEBUG( j <  s );
        if ( i < j )
            swap( i, j );
        return _data[ i * ( i + 1 ) / 2 + j ];
    }

    void set( const T &val ) {
        for(int i=0;i<nb_terms;++i)
            _data[ i ] = val;
    }

    void resize( int new_nb_rows ) {
        ASSERT_IF_DEBUG( new_nb_rows == s );
    }

    void resize( int new_nb_rows, int new_nb_cols ) {
        ASSERT_IF_DEBUG( new_nb_rows == new_nb_cols );
        resize( new_nb_rows );
    }

    T *ptr() { return _data; }
    const T *ptr() const { return _data; }

    void write_to_stream( Stream &os ) const { write_mat_to_stream( *this, os ); }

private:
    T _data[ nb_terms ];
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
    Specialization Sym Dense dynamic
*/
template<class T_,int p>
class BasicMat<T_,Sym<-1,p>,Dense<> > {
public:
    typedef T_ T;
    typedef int S;

    Mat() : _nb_rows( 0 ), owning( true ) {}

    Mat( const Mat &v ) : _nb_rows( v._nb_rows ), _data( _alloc( v._nb_rows * ( v._nb_rows + 1 ) / 2 ) ), owning( true ) {
        for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
            new( _data + i ) T( v._data[ i ] );
    }

    Mat( SetSize, int nb_rows, int nb_cols = 0 ) : _nb_rows( nb_rows ), _data( _alloc( nb_rows * ( nb_rows + 1 ) / 2 ) ), owning( true ) {
        ASSERT_IF_DEBUG( nb_cols == 0 or nb_rows == nb_cols );
        for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
            new( _data + i ) T;
    }

    template<class T0>
    Mat( SetSize, int nb_rows, int nb_cols, const T0 &v0 ) : _nb_rows( nb_rows ), _data( _alloc( nb_rows * ( nb_rows + 1 ) / 2 ) ), owning( true ) {
        ASSERT_IF_DEBUG( nb_cols == 0 or nb_rows == nb_cols );
        for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
            new( _data + i ) T( v0 );
    }

    Mat &operator=( const Mat &v ) {
        resize( _nb_rows );
        for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
            new( _data + i ) T( v._data[ i ] );
        return *this;
    }

    ~Mat() {
        if ( owning ) {
            for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
                _data[ i ].~T();
            _free( _data );
        }
    }

    S nb_rows() const { return _nb_rows; }
    S nb_cols() const { return _nb_rows; }

    const T &operator()( int i, int j ) const {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        if ( i < j )
            swap( i, j );
        return _data[ i * ( i + 1 ) / 2 + j ];
    }

    T &operator()( int i, int j ) {
        ASSERT_IF_DEBUG( i >= 0 );
        ASSERT_IF_DEBUG( j >= 0 );
        ASSERT_IF_DEBUG( i < sr );
        ASSERT_IF_DEBUG( j < sc );
        if ( i < j )
            swap( i, j );
        return _data[ i * ( i + 1 ) / 2 + j ];
    }

    void set( const T &val ) {
        for(int i=0;i<_nb_rows*(_nb_rows+1)/2;++i)
            _data[ i ] = val;
    }

    void resize( int new_nb_rows ) {
        int ns = new_nb_rows * ( new_nb_rows + 1 ) / 2;
        int os =     nb_rows * (     nb_rows + 1 ) / 2;
        if ( new_nb_rows < _nb_rows ) {
            for( int i=os-1; i>=ns; --i )
                _data[ i ].~T();
        } else if ( ns >= p ) {
            T *old_data = _data;
            _data = reinterpret_cast<T *>( malloc( sizeof( T ) * ns ) );
            for(int i=0;i<os;++i)
                new( _data + i ) T( old_data + i );
            for(int i=os;i<ns;++i)
                new( _data + i ) T;
            for(int i=os-1;i>=0;--i)
                old_data[ i ].~T();
            if ( owning )
                _free( old_data );
        }
        _nb_rows = new_nb_rows;
    }

    void resize( int new_nb_rows, int new_nb_cols ) {
        ASSERT_IF_DEBUG( new_nb_rows == new_nb_cols );
        resize( new_nb_rows );
    }

    T *ptr() { return _data; }
    const T *ptr() const { return _data; }

    void write_to_stream( Stream &os ) const { write_mat_to_stream( *this, os ); }

private:
    void _free( T *ptr ) {
        if ( ptr != reinterpret_cast<T *>( _prer ) )
            free( ptr );
    }

    T *_alloc( int nsi ) {
        if ( nsi <= p )
            return reinterpret_cast<T *>( _prer );
        return reinterpret_cast<T *>( malloc( sizeof( T ) * nsi ) );
    }

    char *_prer[ sizeof( T ) * p ]; // reserved room in stack
    S _nb_rows; // user number of rows
    S _nb_cols; // user number of cols
    S _in_rows; // internal number of rows (for storage)
    S _in_cols; // internal number of cols (for storage)
    T *_data;
    bool owning;
};


}


#endif // METIL_MAT_H
