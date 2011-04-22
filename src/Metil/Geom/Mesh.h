#ifndef MESH_H
#define MESH_H

#include "Geom.h"
#include "ElemList.h"
#include "../BasicVec.h"

BEG_METIL_NAMESPACE;

/**

*/
class Mesh : public Geom {
public:
    Mesh();

protected:
    BasicVec<Ptr<ElemList> > elem_lists;
};

END_METIL_NAMESPACE;

#endif // MESH_H
