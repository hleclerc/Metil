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

#ifndef METIL_ABIDATA_H
#define METIL_ABIDATA_H

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file AbiData.cpp
#endif

namespace Metil {

class String;

/**

*/
class AbiData {
public:
    virtual ~AbiData();
    virtual void *get_symbol( const String &symbol ) = 0;
    virtual String last_error() const = 0;
    virtual operator bool() const = 0;
    
    static AbiData *load( const String &lib_file );
};


}

#endif // METIL_ABIDATA_H
