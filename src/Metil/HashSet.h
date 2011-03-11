#ifndef HASHSET_H
#define HASHSET_H

#include "BasicSplittedVec.h"

BEG_METIL_NAMESPACE;

/**
Example:
\code
struct H { int operator()( int a ) const { return a; } };
struct E { bool operator()( int a, int b ) const { return a == b; } };

int main() {
    HashSet<int,H,E,512> h;
    h.set_item( 10 );
    h.set_item( 20 );

    PRINT( h.get_item(  5 ) );
    PRINT( h.get_item( 10 ) );
}
\endcode
*/
template<class T,class HashOp,class EqOp,int hash_size,int size_splitted_vec=64>
struct HashSet {
    struct Item {
        Item( const T &value ) : value( value ) {}
        T value;
        Item *next;
    };

    HashSet() {
        for( int i = 0; i < hash_size; ++i )
            table[ i ] = 0;
    }

    template<class TV>
    Item *get_item( const TV &value ) { ///< return 0 if not found
        int hash_val = hash_op( value ) % hash_size;
        for( Item *i = table[ hash_val ]; i; i = i->next )
            if ( eq_op( i->value, value ) )
                return i;
        return 0;
    }

    Item *set_item( const T &value ) { ///< assumes item does not exist
        Item *res = items.push_back( value );

        int hash_val = hash_op( value ) % hash_size;
        res->next = table[ hash_val ];
        table[ hash_val ] = res;

        return res;
    }

    EqOp eq_op;
    HashOp hash_op;
    Item *table[ hash_size ];
    BasicSplittedVec<Item,size_splitted_vec> items;
};

END_METIL_NAMESPACE;

#endif // HASHSET_H
