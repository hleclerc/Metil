#include "TypeConstructor_GpuImg.h"
#include "NewAndRefNumber.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_dim__when__a__isa__GpuImg__pert__1( MO a ) {
    return NEW_Number( static_cast<TypeConstructor_GpuImg *>( a.type->constructor )->dim );
}

MO metil_def_base_type__when__a__isa__GpuImg__pert__1( MO a ) {
    return static_cast<TypeConstructor_GpuImg *>( a.type->constructor )->item_type_bas;
}

int TypeConstructor_GpuImg::Owcp_size() const { return 0; }

String TypeConstructor_GpuImg::Owcp_data() const { return "GpuImgData<" + String( dim ) + ">"; }

void TypeConstructor_GpuImg::default_mw( MethodWriter &mw ) const {
    TypeConstructor::default_mw( mw );
    mw.add_include( "Level1/GpuImgData.h" );
}

void TypeConstructor_GpuImg::init( Type *type ) {
    const char *name = type->name + 7;
    dim = String::read_int( name );
    item_type_bas = Type::find_with_name( ++name );
}

END_METIL_LEVEL1_NAMESPACE;
