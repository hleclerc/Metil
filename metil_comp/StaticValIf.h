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

#ifndef METIL_STATICVALIF_H
#define METIL_STATICVALIF_H

namespace Metil {

/** contain static const unsigned val = static_val if want_static_val==true. Contain unsigned val else. */
template<class T,bool want_static_val=true,int static_val>
struct StaticValIf {
    void set(T v) { ASSERT_IF_DEBUG(static_val==v); }
    static const int val = static_val;
};

template<class T,int static_val>
struct StaticValIf<T,false,static_val> {
    void set(T v) { val = v; }
    T val;
};


}

#endif // METIL_STATICVALIF_H

