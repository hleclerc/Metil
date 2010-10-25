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

#ifndef METIL_SYSTEM_H
#define METIL_SYSTEM_H

#include "String.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file System.cpp
#endif

namespace Metil {

String cur_dir(); // current directory
String canonicalize_filename( const String &f ); /// /tata/../grot\toto/ -> /grot/toto
String absolute_filename( const String &f ); /// ./grot//toto/ -> /pouet/grot/toto
int exec_cmd( const String &f );

String directory_of( const String &filename );
String filename_without_dir_of( const String &filename );

int create_directory( const String &filename, bool check_if_exists = true );
long long last_modification_time_or_zero_of_file_named( const String &n );
bool file_exists( const String &n );

void rm( const String &file ); // rm file

String get_os_type();
String get_cpu_type();
bool term_supports_color(); /// return true if terminal supports escape color sequences

/// can be used to sweep a directory
struct DirectoryIterator {
    DirectoryIterator( const String &directory );
    ~DirectoryIterator();
    operator bool() const;
    DirectoryIterator &operator++();
    String operator*() const;

    void *dir;
    void *dir_ent;
};

double time_of_day_in_sec(); /// ~ µs

}

#endif // METIL_SYSTEM_H
