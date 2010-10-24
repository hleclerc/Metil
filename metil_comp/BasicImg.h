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

#ifndef METIL_BASIC_IMG_H
#define METIL_BASIC_IMG_H

//#include "DisplayObjectImage.h"
#include "Number.h"
#include "BasicVec.h"

namespace Metil {


/**
    Specialization Gen Dense static -> tiny matrices (data is not aligned)
*/
template<class T_=double,int dim_=2>
class BasicImg /* : public DisplayableObject*/ {
public:
    typedef T_ T;
    typedef int S;
    typedef BasicVec<int,dim_> V;
    static const int dim = dim_;
    
    BasicImg() {}
    
    BasicImg( SetSize, const V &size ) : _size( size ), _data( SetSize(), (int)product( size ) ) { init_accum(); }

    BasicImg( SetSize, const V &size, T *ptr ) : _size( size ), _data( SetSize(), (int)product( size ), ptr ) { init_accum(); }

    template<class T2>
    BasicImg( SetSize, const V &size, const T2 &val ) : _size( size ), _data( SetSize(), product( size ), val ) { init_accum(); }

    V size() const { return _size; }
    int height() const { return _size[ 1 ]; }
    int width () const { return _size[ 0 ]; }

    const T_ &operator[]( const V &x ) const { ASSERT_IF_DEBUG( all( x >= 0 ) and all( x < _size ) ); return _data[ offset( x ) ]; }
    T_       &operator[]( const V &x )       { ASSERT_IF_DEBUG( all( x >= 0 ) and all( x < _size ) ); return _data[ offset( x ) ]; }
    
    const T &operator()( int x, int y ) const { return _data[ offset( x, y ) ]; }
    T       &operator()( int x, int y )       { return _data[ offset( x, y ) ]; }
    
    void resize( const V &s ) { // get room for s
        _data.resize( product( _size ) );
        _size = s;
        init_accum();
    }
    
    void resize( int nb_x, int nb_y ) { resize( V( nb_x, nb_y ) ); }
    
    T *ptr() { return _data.ptr(); }
    const T *ptr() const { return _data.ptr(); }
    
    void write_to_stream( Stream &os ) const { os << _size; }
    
    //    virtual DisplayObject *new_display_object( DisplayScene *dsc ) const {
    //        return attach_display_object( new DisplayObjectImage( this, dsc, _size, reinterpret_cast<const void *>( _data.ptr() ), type_ptr( StructForType<T_>() ) ) );
    //    }

    template<class ValItem>
    void apply( const BasicVec<int,dim> &x_min, const BasicVec<int,dim> &x_max, ValItem &as ) const {
        apply( x_min, x_max, as, Number<dim>() );
    }

    template<class ValItem>
    void apply_with_grad( const BasicVec<int,dim> &x_min, const BasicVec<int,dim> &x_max, ValItem &as ) const {
        apply_with_grad( x_min, x_max, as, Number<dim>() );
    }

    template<class TP>
    TP linear_interpolation( const BasicVec<TP,2> &x ) const {
        int xi_0 = int( x[0] ), xi_1 = int( x[1] );
        TP  xf_0 = x[0] - xi_0, xf_1 = x[1] - xi_1;
        int s_x = _size[ 0 ], o = xi_0 + s_x * xi_1;
        return _data[ o + 0       ] * ( 1 - xf_0 ) * ( 1 - xf_1 ) +
               _data[ o + 1       ] * ( 0 + xf_0 ) * ( 1 - xf_1 ) +
               _data[ o     + s_x ] * ( 1 - xf_0 ) * ( 0 + xf_1 ) +
               _data[ o + 1 + s_x ] * ( 0 + xf_0 ) * ( 0 + xf_1 );
    }

    void load_ascii_mat_file( const CString &filename ) {
        // sizes
        sizes = 0;
        File f( filename );
        String line;
        if ( getline( f, line ) ) {
            StringStream<String> is( line );
            T val;
            while ( is >> val )
                sizes[0]++;
            sizes[1] = 1;
            while ( getline( f, line ) )
                sizes[1]++;
        }

        // data
        data.resize( product( sizes ) );
        f.clear();
        f.seek( 0 );
        for(unsigned i=0;i<data.size();++i)
            f >> data[ i ];
    }

private:
    template<class ValItem>
    void apply( const BasicVec<int,dim> &x_min, const BasicVec<int,dim> &x_max, ValItem &as, Number<2> ) const {
        BasicVec<int,dim> x;
        int o = x_min[ 0 ] + x_min[ 1 ] * _size[ 0 ];
        for( x[1] = x_min[1]; x[1] < x_max[1]; ++x[1], o += _size[0] - x_max[0] + x_min[0] )
            for( x[0] = x_min[0]; x[0] < x_max[0]; ++x[0], ++o )
                as( x, _data[ o ] );
    }

    template<class ValItem>
    void apply_with_grad( const BasicVec<int,dim> &x_min, const BasicVec<int,dim> &x_max, ValItem &as, Number<2> ) const {
        BasicVec<int,dim> x;
        int s_x = _size[ 0 ], o = x_min[ 0 ] + x_min[ 1 ] * s_x, d_x = s_x - x_max[0] + x_min[0];
        for( x[1] = x_min[1]; x[1] < x_max[1]; ++x[1], o += d_x )
            for( x[0] = x_min[0]; x[0] < x_max[0]; ++x[0], ++o )
                as( x, _data[ o ], BasicVec<double,2>(
                        0.5 * ( _data[ o +   1 ] - _data[ o -   1 ] ),
                        0.5 * ( _data[ o + s_x ] - _data[ o - s_x ] )
                ) );
    }


    inline int offset( const V &x, Number<1> ) const { return x[ 0 ]; }
    inline int offset( const V &x, Number<2> ) const { return x[ 0 ] + _size[0] * x[ 1 ]; }
    inline int offset( const V &x, Number<3> ) const { return x[ 0 ] + _size[0] * x[ 1 ] + _accum[ 0 ] * x[ 2 ]; }

    inline int offset( const V &x ) const { return offset( x, Number<dim>() ); }

    inline int offset( int x, int y ) const { return x + _size[0] * y; }

    inline void init_accum() {
        if ( dim < 3 )
            return;
        int acc = _size[ 0 ];
        for(int i=2;i<dim;++i) {
            acc *= _size[ i ];
            _accum[ i - 2 ] = acc;
        }
    }
    
    V _size;
    BasicVec<T_,( dim -2 > 0 ? dim - 2 : 0 )> _accum; // _size[0] * _size[1], _size[0] * _size[1] * _size[2], ...
    BasicVec<T_> _data;
};

}


#endif // METIL_BASIC_IMG_H
