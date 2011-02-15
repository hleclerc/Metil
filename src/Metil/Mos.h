#ifndef MOS_H
#define MOS_H

#include "String.h"

BEG_METIL_LEVEL1_NAMESPACE;

class Mos {
public:
    Mos() {}
    Mos( String base ) : base( base ), data( base + ".data"), type( base + ".type" ) {}
    Mos( String data, String type ) : data( data ), type( type ) {}

    Mos &operator=( String base ) {
        this->base = base;
        this->data = base + ".data";
        this->type = base + ".type";
        return *this;
    }

    void write_str( String &os ) const { os << base; }

    String base;
    String data;
    String type;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // MOS_H
