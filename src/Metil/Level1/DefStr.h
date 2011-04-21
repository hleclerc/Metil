#ifndef DEFSTR_H
#define DEFSTR_H

#include "../BasicSplittedVec.h"
#include "../BasicVec.h"

#include <string>

BEG_METIL_LEVEL1_NAMESPACE;

class DefStr {
public:
    typedef std::string Str;

    struct Item {
        Item( Str name = "" ) : name( name ) {
            children[ 0 ] = 0;
            children[ 1 ] = 0;
            parent = 0;
            sibling = 0;
            prev = 0;
            next = 0;
        }

        Str name;
        Item *children[ 2 ];
        Item *parent;
        Item *sibling;
        Item *prev, *next;
    };

    struct Operator {
        typedef enum { r = 1, l = 2, lr = 3, n = 4 } Kind;
        Operator( const char *name, Kind type ) : name( name ), type( type ) {}

        const char *name;
        int type;
    };

    DefStr( const Str &file, int line, const Str &orig );
    DefStr( const DefStr &def_str );

    bool operator==( const DefStr &def_str ) const { return def_str.orig == orig; }

    void cond( Str &type, BasicVec<Str> &init ) const;
    FP64 pert() const;
    BasicVec<Str> type_constructors() const;

    Str file;
    int line;
    Str orig;
    Str name;
private:
    static void update_operators();
    static int num_operator( Str name );

    void init( const Str &file, int line, const Str &orig );
    Str item_to_cond_str_rec( Item *item, Str &type, BasicVec<Str> &init, Str arg = "" ) const;
    int num_child( Str name ) const;

    BasicSplittedVec<Item,16> items;
    BasicVec<Item *> byop;

    static int num_first_n_operator;
    static BasicVec<Operator> operators;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // DEFSTR_H
