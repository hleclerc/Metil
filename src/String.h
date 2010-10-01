#ifndef STRING_H
#define STRING_H

#include "Type.h"
#include "Dout.h"

#include <string>

BEG_METIL_NAMESPACE;

struct String : public Level1::MO {
    String() { type = &Level1::metil_type_bas_VoidString; }
    // ~MyString() { CM_1( del, *this ); }
};

typedef std::string BootstrapString;

END_METIL_NAMESPACE;

#endif // STRING_H
