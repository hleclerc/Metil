#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "BasicSplittedVec.h"

BEG_METIL_NAMESPACE;

/**

*/
template<class K,class T,class H,class E,int hash_size,int size_splitted_vec=64>
struct HashTable {
    struct Item {
        Item( const K &key, const T &value ) : key( key ), value( value ) {}
        K key;
        T value;
        Item *next;
    };

    HashTable() {
        for( int i = 0; i < hash_size; ++i )
            table[ i ] = 0;
    }

    Item *get_item( const K &key ) { ///< return 0 if not found
        int hash_val = hash_func( key ) % hash_size;
        for( Item *i = table[ hash_val ]; i; i = i->next )
            if ( eq_func( i->key, key ) )
                return i;
        return 0;
    }

    Item *set_item( const K &key, const T &value ) { ///< return 0 if not found
    }

    E eq_func;
    H hash_func;
    Item *table[ hash_size ];
    BasicSplittedVec<Item,size_splitted_vec> items;
};

END_METIL_NAMESPACE;

#endif // HASHTABLE_H
