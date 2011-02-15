#include "TypeConstructor_ConstCharPtrWithSize.h"
#include "TypeConstructor_FileWithoutClose.h"
#include "OwcpStringData.h"
#include "../String.h"

#include <cstdio>
#include <cstring>

BEG_METIL_LEVEL1_NAMESPACE;

// flush
void metil_def_flush__when__a__isa__FileWithoutClose__pert__1( MO &a ) { fflush( reinterpret_cast<FILE *>( a.data ) ); }

// write
void metil_def_write__when__a__isa__FileWithoutClose__pert__2( MO &a, const void *ptr, ST len ) {
    if ( a.data )
        std::fwrite( ptr, 1, len, reinterpret_cast<FILE *>( a.data ) );
}

// convert_to_Bool
bool metil_def_convert_to_Bool__when__a__isa__FileWithoutClose__pert__1( MO a ) {
    return a.data and not feof( reinterpret_cast<FILE *>( a.data ) );
}

// const char *
void metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__ConstCharPtr__pert__100( MO &a, MO b ) {
    const char *ptr = reinterpret_cast<const char *>( b.data );
    if ( ptr and a.data )
        std::fwrite( ptr, 1, std::strlen( ptr ), reinterpret_cast<FILE *>( a.data ) );
}

// OwcpString
void metil_def_self_append__when__a__isa__FileWithoutClose__and__b__isa__OwcpString__pert__1( MO &a, MO b ) {
    Level1::OwcpStringData *o = reinterpret_cast<Level1::OwcpStringData *>( b.data );
    if ( a.data )
        std::fwrite( o->ptr(), 1, o->size(), reinterpret_cast<FILE *>( a.data ) );
}

// const char * + size
void metil_def_self_append__when__b__isa__ConstCharPtrWithSize__and__a__isa__FileWithoutClose__pert__1( MO &a, MO b ) {
    const TypeConstructor_ConstCharPtrWithSize::Data *o = reinterpret_cast<const TypeConstructor_ConstCharPtrWithSize::Data *>( b.data );
    if ( a.data )
        std::fwrite( o->data, 1, o->size, reinterpret_cast<FILE *>( a.data ) );
}

// ptr_z
const void *metil_def_ptr_z__when__a__isa__FileWithoutClose__pert__1( MO &a ) {
    FILE *f = reinterpret_cast<FILE *>( a.data );
    if ( not f )
        return "";
    ST old = ftell( f );
    fseek( f,   0, SEEK_END );
    ST end = ftell( f );
    fseek( f, old, SEEK_SET );

    NewString res( end - old );
    ST act = fread( res.ptr(), 1, end - old, f );
    // ASSERT( act == end - old, "..." );
    static_cast<String &>( a ) = res;
    return res.ptr();
}

// size
MO metil_def_size__when__a__isa__FileWithoutClose__pert__1( MO a ) {
    FILE *f = reinterpret_cast<FILE *>( a.data );
    if ( not f )
        return &metil_type_cst_Cst_0;
    ST old = ftell( f );
    fseek( f,   0, SEEK_END );
    ST end = ftell( f );
    fseek( f, old, SEEK_SET );
    return NEW_Number( end );
}

MO metil_def_copy__when__a__isa__FileWithoutClose( MO a ) {
    return a;
    //    if ( not a.data )
    //        return a;
    //    return MO( a.data, a.type->bas_type );
}

END_METIL_LEVEL1_NAMESPACE;
