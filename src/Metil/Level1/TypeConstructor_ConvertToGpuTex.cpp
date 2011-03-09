#include "TypeConstructor_ConvertToGpuTex.h"
#include "TypeConstructor_Array.h"

// #include "CudaMetil.h"

BEG_METIL_LEVEL1_NAMESPACE;

void metil_gen_select_C__when__a__isa__ConvertToGpuTex__and__b__isa__Array__pert__1( MethodWriter &mw ) {
    mw.add_include( "CudaMetil.h" );
    mw.add_include( "Metil/Level1/Owcp.h" );
    mw.add_include( "Metil/Level1/GpuTexData.h" );
    TypeConstructor_Array *b = static_cast<TypeConstructor_Array *>( mw.type[ 1 ]->constructor );
    ASSERT( b->item_type_bas, "TODO : conv untyped array -> gpu tex" );
    String type; type << "GpuTex_" << b->dim() << "_" << b->item_type_bas->name;
    mw.add_type_decl( type );
    mw.n << "Type *type = &metil_type_bas_" << type << ";";
    mw.n << "typedef Owcp<0,GpuTexData<" << b->dim() << "> > TR;";
    mw.n << "TR *data = NEW( TR, type );";

    //
    b->write_get_t_header( mw, "AH" );
    b->write_get_header( mw, "h", mw.arg[ 1 ].data, "AH" );
    b->write_get_data_ptr( mw, false, "d", "h", mw.arg[ 1 ].data );
    for( int d = 0; d < b->dim(); ++d )
        mw.n << "data->data.size[ " << d << " ] = " << b->get_size_n( "h", d ) << ";";

    // cudaArray
    // cudaMallocArray()
    if ( b->dim() == 3 ) {
        mw.n << "cudaExtent volumeSize;";
        mw.n << "volumeSize.width  = data->data.size[ 0 ];";
        mw.n << "volumeSize.height = data->data.size[ 1 ];";
        mw.n << "volumeSize.depth  = data->data.size[ 2 ];";
        mw.n << "typedef " << b->item_type_bas->constructor->cpp_type() << " VT;";
        mw.n << "cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<VT>();";
        mw.n << "CSC( cudaMalloc3DArray( &data->data.data, &channelDesc, volumeSize ) );";
        mw.n << "// copy data to 3D array";
        mw.n << "cudaMemcpy3DParms copyParams = { 0 };";
        mw.n << "copyParams.srcPtr   = make_cudaPitchedPtr( d, volumeSize.width * sizeof( VT ), volumeSize.width, volumeSize.height );";
        mw.n << "copyParams.dstArray = data->data.data;";
        mw.n << "copyParams.extent   = volumeSize;";
        mw.n << "copyParams.kind     = cudaMemcpyHostToDevice;";
        mw.n << "CSC( cudaMemcpy3D( &copyParams ) );";
    } else {
        mw.n << "TODO;";
    }

    mw.ret() << "MO( data, type );";
}

//    // set texture parameters
//    tex.normalized = true;                      // access with normalized texture coordinates
//    tex.filterMode = cudaFilterModeLinear;      // linear interpolation
//    tex.addressMode[ 0 ] = cudaAddressModeClamp;  // clamp texture coordinates
//    tex.addressMode[ 1 ] = cudaAddressModeClamp;  //
//    // bind array to 3D texture
//    CSC( cudaBindTextureToArray( tex, d_volumeArray, channelDesc ) );

END_METIL_LEVEL1_NAMESPACE;
