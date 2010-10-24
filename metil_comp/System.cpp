/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#if !defined(__WIN32__) && (defined(_WIN32) || defined(WIN32))
#define __WIN32__
#endif

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#ifndef MINGW
    #include <sys/utsname.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include "System.h"
#include "CommonFunctions.h"

namespace Metil {

String cur_dir() {
    for( unsigned st = 1024; ; st *= 2 ) {
        char *res = (char *)malloc( st );
        if ( getcwd( res, st ) ) {
            String s( res );
            free( res );
            return s;
        }
        free( res );
    }
    return String();
}

String canonicalize_filename( const String &f ) {
    String res; res.reserve( f.size() );
    for(int i=0;i<f.size();++i) {
        if ( f[i]=='.' and i+1<f.size() and ( f[i+1]=='/' or f[i+1]=='\\' ) ) {
            // ../toto
            if ( i and f[i-1]=='.' ) {
                for( int cpt = 2, j = res.size()-1; j >= 0; --j ) {
                    if ( res[j]=='/' or res[j]=='\\' ) {
                        if ( --cpt == 0 ) {
                            res = String( res.data(), res.data() + j );
                            break;
                        }
                    }
                }
            } else
                ++i;
        } else if ( f[i] == '\\' )
            res += '/';
        else
            res += f[i];
    }
    res.rstrip_inplace('/');
    res.rstrip_inplace('\\');
    return res;
}

String absolute_filename( const String &f ) {
    if ( f[0]=='/' or f[0]=='\\' )
        return canonicalize_filename( f );
    String res = cur_dir();
    if ( f != "." )
        res += "/" + f;
    return canonicalize_filename( res );
}


String directory_of( const String &filename ) {
    int pos = filename.rfind( '/' );
    if ( pos < 0 )
        return "";
    return String( filename.data(), filename.data() + pos + 1 );
}

String filename_without_dir_of( const String &filename ) {
    int pos = filename.rfind('/');
    if ( pos < 0 )
        pos = -1;
    return filename.lstrip( pos + 1 );
}

int create_directory( const String &filename, bool check_if_exists ) {
    if ( mkdir( filename.data(), S_IRWXU | S_IRWXG ) ) {
        if ( errno == EEXIST and check_if_exists == false )
            return 0;
        return errno;
    }
    return 0;
}

long long last_modification_time_or_zero_of_file_named( const String &n ) {
    struct stat stat_file;
    if ( stat( n.data(), &stat_file ) )
        return 0;
    return stat_file.st_mtime;
}

bool file_exists( const String &n ) {
    struct stat stat_file;
    return ( stat( n.data(), &stat_file ) == 0 );
}

String get_os_type() {
    #ifdef MINGW
        return "Win";
    #else
        struct utsname utsn;
        uname(&utsn);
        return utsn.sysname;
    #endif
}

String get_cpu_type() {
    #ifdef MINGW
        return sizeof(void *) == 4 ? "i686" : "x86_64"; // TODO !!
    #else
        struct utsname utsn;
        uname(&utsn);
        return utsn.machine;
    #endif
}

bool term_supports_color() {
    const char *c_term = getenv("TERM");
    if ( not c_term )
        return false;
    String term = c_term;
    return term != "dumb";
}

int exec_cmd( const String &f ) {
    return system( f.data() );
}

double time_of_day_in_sec() {
    struct timeval st;
    struct timezone toto;
    gettimeofday( &st, &toto );
    return st.tv_sec + st.tv_usec / 1e6;
}

void rm( const String &n ) {
    unlink( n.data() );
}

DirectoryIterator::DirectoryIterator( const String &directory ) {
    dir = (void *)opendir( directory.data() );
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
    return ((dirent *)dir_ent)->d_name;
}

}
