#include "TypeConstructor_StringConcat.h"
#include "StringHelp.h"
#include "String.h"
#include "Ad.h"

BEG_METIL_LEVEL1_NAMESPACE;

typedef Owcp<2> SC;

void metil_def_self_append__when__a__isa__String__and__b__isa__StringConcat__pert__1( MO &a, MO b ) {
    static_cast<String &>( a ) << reinterpret_cast<const SC *>( b.data )->children[ 0 ].obj;
    static_cast<String &>( a ) << reinterpret_cast<const SC *>( b.data )->children[ 1 ].obj;
}

MO metil_def_size__when__a__isa__StringConcat( MO a ) {
    MO c_0 = reinterpret_cast<const SC *>( a.data )->children[ 0 ].obj;
    MO c_1 = reinterpret_cast<const SC *>( a.data )->children[ 1 ].obj;
    Val s_0 = CM_1( size, c_0 );
    Val s_1 = CM_1( size, c_1 );
    return CM_2( add, s_0, s_1 );
}

void metil_def_copy_data__when__a__isa__StringConcat( MO a, void *ptr, ST size ) {
    MO c_0 = reinterpret_cast<const SC *>( a.data )->children[ 0 ].obj;
    MO c_1 = reinterpret_cast<const SC *>( a.data )->children[ 1 ].obj;
    ST s_0 = Val( CM_1( size, c_0 ) );
    char *str = reinterpret_cast<char *>( ptr );
    CM_1( copy_data, c_0, str +   0, s_0        );
    CM_1( copy_data, c_1, str + s_0, size - s_0 );
}

const void *metil_def_ptr_z__when__a__isa__StringConcat( MO &a ) {
    Ad o( a );
    MO c_0 = reinterpret_cast<const SC *>( a.data )->children[ 0 ].obj;
    MO c_1 = reinterpret_cast<const SC *>( a.data )->children[ 1 ].obj;
    ST s_0 = Val( CM_1( size, c_0 ) );
    ST s_1 = Val( CM_1( size, c_1 ) );
    //
    NewString res( s_0 + s_1 );
    a.type = &metil_type_bas_OwcpString;
    a.data = res.data;
    CM_1( copy_data, c_0, res.ptr() +   0, s_0 );
    CM_1( copy_data, c_1, res.ptr() + s_0, s_1 );
    return res.ptr();
}

const void *metil_def_new_ptr_z__when__a__isa__StringConcat( MO a ) {
    MO c_0 = reinterpret_cast<const SC *>( a.data )->children[ 0 ].obj;
    MO c_1 = reinterpret_cast<const SC *>( a.data )->children[ 1 ].obj;
    ST s_0 = Val( CM_1( size, c_0 ) );
    ST s_1 = Val( CM_1( size, c_1 ) );
    //
    char *res = (char *)std::malloc( s_0 + s_1 + 1 );
    CM_1( copy_data, c_0, res +   0, s_0 );
    CM_1( copy_data, c_1, res + s_0, s_1 );
    res[ s_0 + s_1 ] = 0;
    return res;
}

MO metil_def_select_C__when__a__isa__StringConcat__and__b__isa__Int__pert__1( MO a, MO b ) {
    MO c_0 = reinterpret_cast<const SC *>( a.data )->children[ 0 ].obj;
    MO c_1 = reinterpret_cast<const SC *>( a.data )->children[ 1 ].obj;
    ST s_0 = Val( CM_1( size, c_0 ) );
    // ST s_1 = Val( CM_1( size, c_1 ) );
    ST pos = CM_1( convert_to_SI32, b );
    //
    if ( pos < s_0 )
        return CM_2( select_C, c_0, b );
    Ad n = NEW_Number( pos - s_0 );
    return CM_2( select_C, c_1, n.o );
}

END_METIL_LEVEL1_NAMESPACE;


