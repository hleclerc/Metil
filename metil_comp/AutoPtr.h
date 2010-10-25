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

#ifndef METIL_AUTO_PTR_H
#define METIL_AUTO_PTR_H

namespace Metil {

/**
    auto delete pointed object during destruction
*/
template<class T>
class AutoPtr {
public:
    AutoPtr( T *v = 0 ) : p( v ) {}
    ~AutoPtr() { delete p; }
    
    AutoPtr &operator=( T *v ) {
        delete p;
        p = v;
        return *this;
    }
    
    const T *ptr() const { return p; }
    T *ptr() { return p; }
    
    const T *operator->() const { return p; }
    T *operator->() { return p; }

    const T &operator*() const { return *p; }
    T &operator*() { return *p; }

    operator bool() const { return p; }
    
    T *p;
};

/**
    auto delete pointed object during destruction
*/
template<class T>
class ConstAutoPtr {
public:
    ConstAutoPtr( const T *v = 0 ) : p( v ) {}
    ~ConstAutoPtr() { delete p; }
    
    ConstAutoPtr &operator=( const T *v ) {
        delete p;
        p = v;
        return *this;
    }
    
    const T *ptr() const { return p; }
    
    const T *operator->() const { return p; }
    
    operator bool() const { return p; }
    
    const T *p;
};

}

#endif // METIL_AUTO_PTR_H
