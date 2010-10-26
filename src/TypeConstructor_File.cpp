#include "TypeConstructor_File.h"
#include <stdio.h>

BEG_METIL_LEVEL1_NAMESPACE;

void metil_def_del__when__a__isa__File( MO &a ) {
    if ( a.data )
        fclose( reinterpret_cast<FILE *>( a.data ) );
}

void metil_def_close__when__a__isa__File( MO &a ) {
    if ( a.data )
        fclose( reinterpret_cast<FILE *>( a.data ) );
    a.data = 0;
}

END_METIL_LEVEL1_NAMESPACE;

//#include "MethodFinder.h"
//#include "BasicMethods.h"
//#include "Ad.h"
//
//#include <sys/stat.h>
//#include <cstdio>
//
//BEG_METIL_LEVEL1_NAMESPACE;
//
//static ST size_( const MO &a ) {
//    struct stat info;
//    fstat( fileno( (FILE *)a.data ), &info );
//    return info.st_size;
//}
//
//static void destroy( MO &a ) {
//    std::fclose( (FILE *)a.data );
//}
//
//static void flush  ( MO &a ) {
//    std::fflush( (FILE *)a.data );
//}
//
//static void write( MO &a, const void *p, ST s ) {
//    std::fwrite( p, 1, s, (FILE *)a.data );
//}
//
//static ST read( MO &a, void *p, ST s ) {
//    return std::fread( p, 1, s, (FILE *)a.data );
//}
//
//static MO size( const MO &a ) {
//    return NEW_Number( size_( a ) );
//}
//
//static void *new_ptr( const MO &a ) {
//    ST s = size_( a );
//    char *res = (char *)std::malloc( s + 1 );
//    int r = std::fread( res, 1, s, (FILE *)a.data );
//    res[ r ] = 0;
//    return res;
//}
//
//static void *ptr( MO &a ) {
//    Ad old( a );
//    void *res = new_ptr( a );
//    #ifdef METIL_BOOSTRAP
//    a.type = &type_StringBootstrap;
//    a.data = res;
//    #else // METIL_BOOSTRAP
//    TODO;
//    #endif // METIL_BOOSTRAP
//    return res;
//}
//
//static void write_str( const MO &a, String &os ) {
//    char *p = (char *)new_ptr( a );
//    os << p;
//    std::free( p );
//}
//
//void TypeConstructorStringFile::init( Type *type ) {
//    TypeConstructorString::init( type );
//
//    REG_MET( del      , C0_IS_A( StringFile ), 1, destroy       );
//    REG_MET( destroy  , C0_IS_A( StringFile ), 1, destroy       );
//    REG_MET( free     , C0_IS_A( StringFile ), 1, do_nothing_VO );
//    REG_MET( flush    , C0_IS_A( StringFile ), 1, flush         );
//    REG_MET( new_ptr  , C0_IS_A( StringFile ), 1, new_ptr       );
//    REG_MET( new_ptr_z, C0_IS_A( StringFile ), 1, new_ptr       );
//    REG_MET( ptr      , C0_IS_A( StringFile ), 1, ptr           );
//    REG_MET( ptr_z    , C0_IS_A( StringFile ), 1, ptr           );
//    REG_MET( size     , C0_IS_A( StringFile ), 1, size          );
//
//    REG_MET( write_str, C0_IS_A( StringFile ), 1, write_str     );
//    REG_MET( write    , C0_IS_A( StringFile ), 1, write         );
//    REG_MET( read     , C0_IS_A( StringFile ), 1, read          );
//}
//
///// a StringFile without destructor
//void TypeConstructorStringFileWithoutClose::init( Type *type ) {
//    TypeConstructorStringFile::init( type );
//
//    REG_MET( del    , C0_IS_A( StringFileWithoutClose ), 2, do_nothing_VO );
//    REG_MET( destroy, C0_IS_A( StringFileWithoutClose ), 2, do_nothing_VO );
//}
//
//END_METIL_LEVEL1_NAMESPACE;
