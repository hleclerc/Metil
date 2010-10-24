#ifndef FIELD_H
#define FIELD_H

#include "CString.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Field.cpp
#endif

namespace Metil {

class FieldItem;

/**
*/
class Field {
public:
    Field();
    Field( const CString &filename );
    ~Field();

private:
    const FieldItem *item;
};

} // namespace Metil

#endif // FIELD_H
