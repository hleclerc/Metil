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

#ifndef METIL_MatStdStructuresAndStorages_H
#define METIL_MatStdStructuresAndStorages_H

namespace Metil {


/// Structure pr -> prereservation (data on stack for small dynamic matrices)
template<int sr=-1,int sc=-1,int p=0>
struct Gen { };

/// Structure p -> prereservation (data on stack for small dynamic matrices)
template<int s=-1,int p=0>
struct Sym { };

/// Storage
template<bool row_ordered=true>
struct Dense { };


///
template<class S,int alignment>
struct ValAndCeilVal {
    ValAndCeilVal( S v ) : _val( v ), _ceil_val( ceil( v, alignment ) ) {}
    inline S ceil_val() { return _ceil_val; }
    inline S      val() { return      _val; }
    S _val, _ceil_val;
};

///
template<class S>
struct ValAndCeilVal<S,1> {
    ValAndCeilVal( S v ) : _val( v ) {}
    inline S ceil_val() { return _val; }
    inline S      val() { return _val; }
    S _val;
};

}


#endif // METIL_MatStdStructuresAndStorages_H
