#ifndef IMGITEM_H
#define IMGITEM_H

#include "LazyObject.h"
// #include "Type.h"
// #include "BasicVec.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file ImgItem.cpp
#endif


namespace Metil {

class ValItem;
// class ImgItemGrid;
// class CString;

/**
*/
class ImgItem : public LazyObject {
public:
    virtual ValItem *nb_dim() const = 0;

    // operators
    // virtual const ImgItemGrid *as_grid_of_type( const Type *type ) const;
    // virtual const LazyObject *save( const CString &filename ) const;
    // virtual void write_in_grid( const ImgItemGrid *grid ) const = 0;
};

} // namespace Metil

#endif // IMGITEM_H
