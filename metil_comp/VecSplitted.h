#ifndef VECSPLITTED_H
#define VECSPLITTED_H

#include "BasicVec.h"

namespace Metil {

/**

*/
template<class T,int size_advice>
class VecSplitted {
public:
    struct Item {
        Item *prev;
        Item *next;
        int size;
        int rese; // must be != 0 (see Assign...)
        T data[ 32 ];
    };
    static const int sizeof_Item = sizeof( Item ) - 32 * sizeof( T );

    VecSplitted() : first( 0 ), last( 0 ) {}

    template<class TV>
    VecSplitted( const TV          &vec ) : first( 0 ), last( 0 ) { PushBack<VecSplitted> pb( *this ); vec.apply( pb ); }

    VecSplitted( const VecSplitted &vec ) : first( 0 ), last( 0 ) { PushBack<VecSplitted> pb( *this ); vec.apply( pb ); }

    VecSplitted &operator=( const VecSplitted &vec ) {
        _free();
        first = 0;
        last  = 0;
        PushBack<VecSplitted> pb( *this );
        vec.apply( pb );
        return *this;
    }

    ~VecSplitted() {
        _free();
    }

    T *push_back() {
        if ( last == 0 or last->size == last->rese )
            make_new_item( size_advice );
        T *res = last->data + last->size++;
        new( res ) T();
        return res;
    }

    template<class T0>
    T *push_back( const T0 &v0 ) {
        if ( last == 0 or last->size == last->rese )
            make_new_item( size_advice );
        T *res = last->data + last->size++;
        new( res ) T( v0 );
        return res;
    }

    template<class T0,class T1>
    T *push_back( const T0 &v0, const T1 &v1 ) {
        if ( last == 0 or last->size == last->rese )
            make_new_item( size_advice );
        T *res = last->data + last->size++;
        new( res ) T( v0, v1 );
        return res;
    }

    template<class ValItem> void apply( const ValItem &op ) const { for( Item *i=first; i; i = i->next ) for(int j=0;j<i->size;++j) op( i->data[ j ] ); }
    template<class ValItem> void apply(       ValItem &op ) const { for( Item *i=first; i; i = i->next ) for(int j=0;j<i->size;++j) op( i->data[ j ] ); }
    template<class ValItem> void apply( const ValItem &op )       { for( Item *i=first; i; i = i->next ) for(int j=0;j<i->size;++j) op( i->data[ j ] ); }
    template<class ValItem> void apply(       ValItem &op )       { for( Item *i=first; i; i = i->next ) for(int j=0;j<i->size;++j) op( i->data[ j ] ); }

    void write_to_stream( Stream &os ) const {
        WriteToStream ws( os );
        apply( ws );
    }

private:
    void _free() {
        for( Item *i=last; i;  ) {
            Item *o = i;
            for(int n=o->size-1;n>=0;--n)
                i->data[ n ].~T();
            i = i->prev;
            free( o );
        }
    }

    Item *make_new_item( int size ) {
        Item *old_last = last;
        last = (Item *)malloc( sizeof_Item + size_advice * sizeof( T ) );
        //
        if ( old_last )
            old_last->next = last;
        else
            first = last;
        last->prev = old_last;
        last->next = 0;
        last->size = 0;
        last->rese = size_advice;
        return last;
    }


    Item *first, *last;
};

}

#endif // VECSPLITTED_H
