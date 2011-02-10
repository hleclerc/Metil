/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESST FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef METIL_StringWithSepInCppLine_H
#define METIL_StringWithSepInCppLine_H

#include "MetilString.h"

BEG_METIL_NAMESPACE;

/**

*/
class StringWithSepInCppLine {
public:
    StringWithSepInCppLine( String &string, const char *sep, const char *end ) : string( string ), sep( sep ), end( end ) {}
    ~StringWithSepInCppLine() { if ( end ) string << end; }

    ///
    template<class T>
    StringWithSepInCppLine &operator<<( const T &val ) {
        if ( sep )
            string << sep;
        string << val;
        return *this;
    }

    String &string;
    const char *sep;
    const char *end;
};


/**

*/
class StringWithSepInCppLineMaker {
public:
    StringWithSepInCppLineMaker( String &string, const char *sep = 0, const char *end = "\n" ) : string( string ), sep( sep ), end( end ) {}

    ///
    template<class T>
    StringWithSepInCppLine operator<<( const T &val ) {
        string << val;
        return StringWithSepInCppLine( string, sep, end );
    }

    String &string;
    const char *sep;
    const char *end;
};


END_METIL_NAMESPACE


#endif // METIL_StringWithSepInCppLine_H
