#include "TypeConstructor_GpuTex.h"
#include "NewAndRefNumber.h"
#include "GpuImgData.h"
#include "../Vec.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_dim__when__a__isa__GpuTex__pert__1( MO a ) {
    return NEW_Number( static_cast<TypeConstructor_GpuTex *>( a.type->constructor )->dim );
}

MO metil_def_base_type__when__a__isa__GpuTex__pert__1( MO a ) {
    return static_cast<TypeConstructor_GpuTex *>( a.type->constructor )->item_type_bas;
}

MO metil_def_sizes__when__a__isa__GpuTex__pert__1( MO a ) {
    TypeConstructor_GpuTex *c = static_cast<TypeConstructor_GpuTex *>( a.type->constructor );
    Owcp<0,GpuImgData<3> > *o = reinterpret_cast<Owcp<0,GpuImgData<3> > *>( a.data );
    ASSERT( c->dim == 3, "TODO..." );
    MO res;
    new( &res ) Vec( o->data.size[ 0 ], o->data.size[ 1 ], o->data.size[ 2 ] );
    return res;
}

int TypeConstructor_GpuTex::Owcp_size() const { return 0; }

String TypeConstructor_GpuTex::Owcp_data() const { return "GpuTexData<" + String( dim ) + ">"; }

void TypeConstructor_GpuTex::default_mw( MethodWriter &mw ) const {
    TypeConstructor::default_mw( mw );
    mw.add_include( "Metil/Level1/GpuTexData.h" );
}

void TypeConstructor_GpuTex::init( Type *type ) {
    const char *name = type->name + 7;
    dim = String::read_int( name );
    item_type_bas = Type::find_with_name( ++name );
}

END_METIL_LEVEL1_NAMESPACE;
