#ifndef FIELDITEM_H
#define FIELDITEM_H

#include "LazyObject.h"
#include "Type.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file FieldItem.cpp
#endif

namespace Metil {

/**
*/
class FieldItem : public LazyObject {
public:
    FieldItem();
    virtual ~FieldItem();
    
    virtual const Type *type() const = 0;
};

} // namespace Metil

#endif // FIELDITEM_H
