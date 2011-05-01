#ifndef MESH_H
#define MESH_H

#include "Geom.h"
#include "MeshItem.h"

BEG_METIL_NAMESPACE;

/**

*/
class Mesh : public Geom {
public:
    Mesh();

protected:
    Ptr<MeshItem> item() { return static_cast<MeshItem *>( this->_item.ptr() ); }
};

END_METIL_NAMESPACE;

#endif // MESH_H
