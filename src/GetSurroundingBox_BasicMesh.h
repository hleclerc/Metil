#ifndef GETSURROUNDINGBOX_BASICMESH_H
#define GETSURROUNDINGBOX_BASICMESH_H

#include "DisplayTrans.h"
#include "BasicMesh_Compacted.h"

BEG_METIL_NAMESPACE;

/// use trans if != 0
void get_surrounding_box( float *mi, float *ma, BasicMesh_Compacted *m, DisplayTrans *trans, int w, int h );

END_METIL_NAMESPACE;

#endif // GETSURROUNDINGBOX_BASICMESH_H
