#ifndef IMGITEMFUNCTION_H
#define IMGITEMFUNCTION_H

#include "ImgItemGrid.h"
#include "Number.h"

namespace Metil {

/**
*/
template<class T,int dim>
class ImgItemFunction : public ImgItem {
public:
    typedef T F( int, int );

    ImgItemFunction( F *f, const BasicVec<int,dim> &size ) : _size( size ), _function( f ) {}

    virtual int nb_dim() const { return dim; }
    virtual int size( int d ) const { return _size[ d ]; }
    virtual int nb_planes() const { return 1; }
    virtual const Type *type() const { return type_ptr( StructForType<T>() ); }

    virtual bool done() const { return true; }
    virtual void exec_node() const {}

    virtual void write_in_grid( const ImgItemGrid *grid ) const { write_in_grid( grid, Number<dim>() ); }

protected:
    // 2D
    void write_in_grid( const ImgItemGrid *grid, Number<2> ) const {
        grid->allocate();
        void *data = grid->data();
        BasicVec<T> line( SetSize(), _size[ 0 ] );
        for(int y=0;y<_size[1];++y) {
            for(int x=0;x<_size[0];++x)
                line[ x ] = _function( x, y );
            grid->write_line( data, line.ptr() );
        }
    }

    BasicVec<int,dim> _size;
    F *_function;
};

} // namespace Metil


#endif // IMGITEMFUNCTION_H
