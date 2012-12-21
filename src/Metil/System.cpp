#include "System.h"

#include <stdlib.h>   // system
#include <sys/time.h> // time_of_day_in_sec()
#include <unistd.h>   // getcwd
#include <sys/stat.h> // mkdir...
#include <errno.h>    // errno
#include <dirent.h>   // opendir
#include <string.h>   // strlen
#ifndef WIN32
    #include <sys/utsname.h>
#endif
// #include <stdio.h>   // system

BEG_METIL_NAMESPACE

String cur_dir() {
    for( ST rese = 128; ; rese *= 2 ) {
        NewString res( rese );
        if ( getcwd( res.ptr(), rese ) ) {
            res.set_size( strlen( res.ptr() ) );
            return res;
        }
        res.del();
    }
    return String();
}

String get_env( String var ) {
    const char *res = getenv( var.c_str() );
    return res ? String( res ) : String();
}

void set_env( String var, String val ) {
    #ifdef WIN32
    putenv( ( var + "=" + val ).c_str() );
    #else
    setenv( var.c_str(), val.c_str(), true );
    #endif
}

inline static bool sep( char s ) {
    return s == '/' or s == '\\';
}

String canonicalize_filename( const String &filename ) {
    // ./ or .// or .\ ... at the beginning
    const char *b = filename.c_str();
    if ( b[0]=='.' and sep( b[1] ) ) {
        b += 2;
        while ( sep( b[0] ) )
            ++b;
    }

    if ( not b[ 0 ] )
        return ".";

    // / or \ at the end
    const char *e = b + strlen( b ) - 1;
    while ( e >= b and sep( e[ 0 ] ) )
        --e;
    if ( e < b ) // if contains only separators
        return "/";
    ++e;

    //
    NewString res( e - b + 1 );
    char *bas = res.ptr(), *str = bas;
    for(const char *f = b; f < e; ++f ) {
        if ( sep( f[ 0 ] ) ) { // /
            if ( f[ 1 ] == '.' ) { // .
                if ( f + 2 == e and f != b ) // "something/." at the end
                    break;
                if ( f[ 2 ] == '.' ) { // /..
                    if ( f == b ) { // "/..xxx" at the beginning (weird...)
                        f += 2;
                        *(str++) = '/';
                        *(str++) = '.';
                        *(str++) = '.';
                        continue;
                    }
                    while ( str >= bas and not sep( *(--str) ) );
                    f += 2;
                    continue;
                }
            }
        }
        if ( f[ 0 ] == '.' ) {
            if ( f[ 1 ] == '.' ) { // ".." but no "/.."
                *(str++) = '.';
                *(str++) = '.';
                ++f;
                continue;
            }
            if ( sep( f[ 1 ] ) ) { // "./"
                ++f;
                continue;
            }
        }

        //
        if ( sep( f[0] ) ) {
            if ( sep( f[ 1 ] ) ) {
                ++f;
                continue;
            }
            *(str++) = '/';
            continue;
        }

        *(str++) = f[0];
    }

    //
    if ( str == bas ) // void
        *( str++ ) = '.';
    str[ 0 ] = 0;

    res.set_size( str - bas );

    //
    //PRINT( filename );
    //PRINT( res.ptr() );
    return res;
}

String absolute_filename( const String &f ) {
    if ( not f )
        return f;
    if ( f[ 0 ] == '/' or f[ 0 ] == '\\' )
        return canonicalize_filename( f );
    return canonicalize_filename( cur_dir() + '/' + f );
}

String directory_of( const String &filename ) {
    ST pos = filename.rfind( '/' );
    if ( pos < 0 )
        return String();
    return filename.beg_upto( pos );
}

String filename_without_dir_of( const String &filename ) {
    ST pos = filename.rfind('/');
    if ( pos < 0 )
        pos = -1;
    return filename.end_from( pos + 1 );
}

String filename_with_dir_of( const String &filename ) {
    return canonicalize_filename( filename ).replace( '/', '_' ).replace( '.', '_' );
    //    NewString res( filename.size(), filename.size() );
    //    char *o = res.ptr();
    //    for( const char *p = filename.c_str(); *p; ++p, ++o )
    //        *o = *p == '/' or *p == '.' ? '_' : *p;
    //    return res;
}

double time_of_day_in_sec() {
    struct timeval st;
    struct timezone toto;
    gettimeofday( &st, &toto );
    return st.tv_sec + st.tv_usec / 1e6;
}

int mkdir( const String &filename, bool check_if_exists ) {
    #ifdef WIN32
    if ( ::mkdir( filename.c_str()/* , S_IRWXU| S_IRWXG*/ ) ) {
    #else
    if ( ::mkdir( filename.c_str() , S_IRWXU| S_IRWXG ) ) {
    #endif
        if ( errno == EEXIST and check_if_exists == false )
            return 0;
        return errno;
    }
    return 0;
}

SI64 last_modification_time_or_zero_of_file_named( const char *n ) {
    if ( not n )
        return 0;
    struct stat stat_file;
    if ( stat( n, &stat_file ) )
        return 0;
    return stat_file.st_mtime;
}

SI64 last_modification_time_or_zero_of_file_named( const String &n ) {
    return last_modification_time_or_zero_of_file_named( n.c_str() );
}

bool file_exists( const String &n ) {
    struct stat stat_file;
    return ( stat( n.c_str(), &stat_file ) == 0 );
}

bool is_a_directory( const String &n ) {
    struct stat stat_file;
    if ( stat( n.c_str(), &stat_file ) )
        return false;
    return S_ISDIR( stat_file.st_mode );
}

//void rm( const String &n ) {
//    unlink( n.c_str() );
//}

String get_os_type() {
    #ifdef WIN32
        return "Win";
    #else
        struct utsname utsn;
        uname(&utsn);
        return String( NewString( utsn.sysname ) );
    #endif
}

String get_cpu_type() {
    #ifdef WIN32
        return sizeof(void *) == 4 ? "i686" : "x86_64"; // TODO !!
    #else
        struct utsname utsn;
        uname(&utsn);
        return String( NewString( utsn.machine ) );
    #endif
}

ST get_total_system_memory() {
    ST pages = sysconf( _SC_PHYS_PAGES );
    ST page_size = sysconf( _SC_PAGE_SIZE );
    return pages * page_size;
}

int get_nb_cpu_cores() {
    return sysconf( _SC_NPROCESSORS_ONLN );
}

//bool term_supports_color() {
//    const char *c_term = getenv("TERM");
//    if ( not c_term )
//        return false;
//    return String( c_term ) != "dumb";
//}

DirectoryIterator::DirectoryIterator( const String &directory ) {
    dir = (void *)opendir( directory.c_str() );
    dir_ent = dir ? (void *)readdir( (DIR *)dir ) : 0;
}
DirectoryIterator::~DirectoryIterator() {
    if ( dir )
        closedir( (DIR *)dir );
}
DirectoryIterator::operator bool() const {
    return dir_ent;
}
DirectoryIterator &DirectoryIterator::operator++() {
    dir_ent = dir ? (void *)readdir( (DIR *)dir ) : 0;
    return *this;
}
String DirectoryIterator::operator*() const {
    return NewString( ((dirent *)dir_ent)->d_name );
}

int exec_cmd( String f, bool display ) {
    if ( not f )
        return 0;
    if ( display )
        coutn << f;
    return system( f.c_str() ) != 0;
}

END_METIL_NAMESPACE
