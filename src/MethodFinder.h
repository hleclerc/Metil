#ifndef METHODFINDER_H
#define METHODFINDER_H

#include "TypeConstructor.h"
#include "MethodCond.h"
#include "MethodName.h"
#include <cstdio>

BEG_METIL_LEVEL1_NAMESPACE;

template<class N>
class MethodFinder {
public:
    typedef typename N::TM TM;
    typedef MethodCond Cond;

    struct Item {
        Item *prev;
        Cond *cond;
        TM   *meth;
    };

    ///
    static void abort_msg( const char *msg, Type *type_0, Type *type_1, Type *type_2, bool call_abort = true ) {
        std::fprintf( stderr, "%s for method '%s'", msg, N::get_name() );
        if ( type_2 )
            std::fprintf( stderr, " and types '%s', '%s' and '%s'", type_0->name, type_1->name, type_2->name );
        else if ( type_1 )
            std::fprintf( stderr, " and types '%s' and '%s'", type_0->name, type_1->name );
        else if ( type_0 )
            std::fprintf( stderr, " and type '%s'", type_0->name );
        std::fprintf( stderr, "\n" );
        if ( call_abort )
            abort_or_throw();
    }

    ///
    static TM *find( Type *type_0, Type *type_1 = 0, Type *type_2 = 0/*, bool abort_if_pb = true*/ ) {
        //DOUT( );
        return last->meth;
        //        abort_msg( "impossible to find definition", type_0, type_1, type_2 );
        //        return 0;
    }

    static Item *last;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODFINDER_H
