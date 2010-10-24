#ifndef IMGITEMTIF_H
#define IMGITEMTIF_H

#include "ImgItem.h"

namespace Metil {

/**
*/
class ImgItemTif : public ImgItem {
public:
    ImgItemTif( const CString &filename ) : _filename( filename ), _type( 0 ) {}

    virtual bool done() const { return true; }
    virtual void exec_node() const {}

    virtual int nb_dim() const { update_data_if_necessary(); return 2; }
    virtual int size( int d ) const { update_data_if_necessary(); return _size[ d ]; }
    virtual int nb_planes() const { update_data_if_necessary(); return _nb_planes; }
    virtual const Type *type() const { update_data_if_necessary(); return _type; }

    virtual void write_in_grid( const ImgItemGrid *grid ) const {
        ASSERT( 0, "TODO" );
    }

private:
    void update_data_if_necessary() const {
        ASSERT( 0, "TODO" );
    }

    CString _filename;
    mutable BasicVec<int,2> _size;
    mutable int _nb_planes;
    mutable const Type *_type;
};

} // namespace Metil


#endif // IMGITEMTIF_H
