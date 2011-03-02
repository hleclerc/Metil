#include "TypeConstructor_DistantObject.h"
#include "MethodFinder.h"

BEG_METIL_LEVEL1_NAMESPACE;


void TypeConstructor_DistantObject::default_mw( MethodWriter &mw ) const {
    // mw.add_include( "Metil/Level1/DistantObjectData.h" );
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
