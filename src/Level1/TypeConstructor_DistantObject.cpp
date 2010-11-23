#include "TypeConstructor_DistantObject.h"
#include "MethodFinder.h"

BEG_METIL_LEVEL1_NAMESPACE;

//static TypeConstructor_DistantObject *sc( Type *type ) {
//    return static_cast<TypeConstructor_DistantObject *>( type->constructor );
//}


//#define DECL_MET( T, N ) \
//    void metil_gen_##N##__when__a__isa__DistantObject__pert_100( MethodWriter &mw, const Mos *args, const String &ret ) { \
//        if ( not call_gene<MethodName_##N>( mw, static_cast<TypeConstructor_DistantObject *>( mw.get_type( 0 )->constructor )->base_type, mw.get_type( 1 ), mw.get_type( 2 ), args, ret, false ) ) mw.n << "ERROR(\"not defined\");"; \
//    }
//#include "DeclMethodsUnary.h"
//#undef DECL_MET

//#define DECL_MET( T, N ) \
//    void metil_gen_##N##__when__a__isa__DistantObject__pert_100( MethodWriter &mw, const Mos *args, const String &ret ) { \
//        if ( not call_gene<MethodName_##N>( mw, static_cast<TypeConstructor_DistantObject *>( mw.get_type( 0 )->constructor )->base_type, mw.get_type( 1 ), mw.get_type( 2 ), args, ret, false ) ) mw.n << "ERROR(\"not defined\");"; \
//    }
//#include "DeclMethodsBinary.h"
//#undef DECL_MET


void TypeConstructor_DistantObject::default_mw( MethodWriter &mw ) const {
    // mw.add_include( "Level1/DistantObjectData.h" );
    if ( base_type )
        base_type->constructor->default_mw( mw );
}

void TypeConstructor_DistantObject::init( Type *type ) {
     const char *name = type->name + 11;

    // provenance
     provenance = MachineId::type( NewString( name, name + 3 ) );

     // type_name
     base_type = Type::find_with_name( name + 4 );
     ASSERT( base_type, "type %s not found", name + 4 );
}

END_METIL_LEVEL1_NAMESPACE;
