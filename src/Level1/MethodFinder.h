#ifndef METHODFINDER_H
#define METHODFINDER_H

#include "TypeConstructor.h"
#include "MethodWriter.h"
#include "MethodCond.h"
#include "MethodName.h"
#include "Dout.h"

#include <cstdio>

BEG_METIL_LEVEL1_NAMESPACE;

template<class N>
class MethodFinder {
public:
    typedef MethodMaker TG;
    typedef typename N::TM TM;
    typedef MethodCond Cond;
    typedef const char *CCHP;

    struct Item {
        Item *prev;
        Cond *cond;
        TM   *meth;
        TG   *gene;
        FP64  pert;
        CCHP  file;
        int   line;
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
    static Item *find_item( Type *type_0, Type *type_1 = 0, Type *type_2 = 0,
                           bool abort_if_pb = true, bool want_gen_only = false ) {
        if ( type_0 ) type_0->init_if_necessary();
        if ( type_1 ) type_1->init_if_necessary();
        if ( type_2 ) type_2->init_if_necessary();

        // find items with greater pertinence and checked cond
        BasicVec<Item *,-1,4> res;
        for( Item *item = last; item; item = item->prev ) {
            if ( item->cond->valid( type_0, type_1, type_2 ) and (
                        want_gen_only == false or item->gene ) ) {
                if ( res.size() ) {
                    if ( item->pert < res[ 0 ]->pert )
                        continue;
                    if ( item->pert > res[ 0 ]->pert )
                        res.resize( 0 );
                }
                res << item;
            }
        }

        if ( abort_if_pb ) {
            // first case -> nothing
            if ( res.size() == 0 )
                abort_msg( "impossible to find definition", type_0, type_1, type_2 );

            // second case -> Ambiguous overload
            if ( res.size() >= 2 and abort_if_pb ) {
                abort_msg( "ambiguous overload", type_0, type_1, type_2, false );
                for(ST i=0;i<res.size();++i)
                    std::fprintf( stderr, "%s:%i: possible surdefinition\n", res[ i ]->file, res[ i ]->line );
                abort_or_throw();
            }
        }

        // else -> ok
        return res.size() == 1 ? res[ 0 ] : 0;
    }

    ///
    static TM *find( Type *type_0, Type *type_1 = 0, Type *type_2 = 0, bool abort_if_pb = true ) {
        Item *item = find_item( type_0, type_1, type_2, abort_if_pb );

        // maybe we have to generate / load the code
        if ( not item->meth ) {
            DynamicLibrary &dl = MethodWriter::get_lib_for_types( type_0, type_1, type_2, item->file );
            String sym = MethodWriter::symb_of( N::get_name(), type_0, type_1, type_2, false );
            TM *res = (TM *)dl.get_sym( sym );
            ASSERT( res, "%s not found", sym.c_str() );
            return res;
        }

        return item->meth;
    }

    static Item *last;
};

template<class MethodName>
void call_gene( MethodWriter &cw, Type *type_0, Type *type_1, Type *type_2, Mos *a, const String &ret = "return " ) {
    typedef MethodFinder<MethodName> MF;
    typename MF::Item *item = MF::find_item( type_0, type_1, type_2, true, true );
    MethodWriter mw( type_0, type_1, type_2 );
    item->gene( mw, a, ret );
    cw << mw.code;
    for( int i = 0; i < mw.includes.size(); ++i )
        cw.includes << mw.includes[ i ];
    cw.preliminary << mw.preliminary;
}

END_METIL_LEVEL1_NAMESPACE;

#endif // METHODFINDER_H
