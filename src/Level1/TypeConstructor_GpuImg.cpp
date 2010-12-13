#include "TypeConstructor_GpuImg.h"
#include "TypeConstructor_Array.h"
#include "NewAndRefNumber.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_dim__when__a__isa__GpuImg__pert__1( MO a ) {
    return NEW_Number( static_cast<TypeConstructor_GpuImg *>( a.type->constructor )->dim );
}

MO metil_def_base_type__when__a__isa__GpuImg__pert__1( MO a ) {
    return static_cast<TypeConstructor_GpuImg *>( a.type->constructor )->item_type_bas;
}

void metil_gen_allocate_2__when__a__isa__GpuImg__and__b__isa__Array__pert__1( MethodWriter &mw ) {
    mw.add_include( "CudaMetil.h" );
    mw.add_include( "Vec.h" );

    TypeConstructor_GpuImg *a = static_cast<TypeConstructor_GpuImg *>( mw.type[ 0 ]->constructor );
    TypeConstructor_Array  *b = static_cast<TypeConstructor_Array  *>( mw.type[ 1 ]->constructor );
    int dim = b->dim();
    mw.n << "typedef Owcp<0,GpuImgData<" << dim << "> > TR;";
    mw.n << "const Vec &s = static_cast<const Vec &>( " << mw.arg[ 1 ] << " );";
    mw.n << "TR *res = NEW( TR, " << mw.arg[ 0 ].type << " );";
    for( int d = 0; d < dim; ++d )
        mw.n << "res->data.size[ " << d << " ] = s[ " << d << " ];";

    // rese
    mw << "ST rese = " << a->item_type_bas->constructor->static_size_in_bytes();
    for( int d = 0; d < dim; ++d )
        mw << " * res->data.size[ " << d << " ]";
    mw.n << ";";

    mw.n << "cudaMalloc( &res->data.data, rese );";
    mw.n << mw.arg[ 0 ].data << " = res;";
    mw.ret() << "res->data.data;";
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
    PRINT( item_type_bas->name );
    ASSERT( item_type_bas, "%s not found", type->name );
}

END_METIL_LEVEL1_NAMESPACE;
