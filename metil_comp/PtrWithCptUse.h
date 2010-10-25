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
#ifndef METIL_PtrWithCptUse_H
#define METIL_PtrWithCptUse_H

namespace Metil {

/**

*/
template<class T>
class PtrWithCptUse {
public:
    PtrWithCptUse() : p( 0 ) { }
    
    PtrWithCptUse( T             *v ) : p( v   ) { if ( v ) ++v->cpt_use; }
    PtrWithCptUse( PtrWithCptUse &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }

    PtrWithCptUse( const T             *v ) : p( v   ) { if ( v ) ++v->cpt_use; }
    PtrWithCptUse( const PtrWithCptUse &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }

    template<class T2>
    PtrWithCptUse( const PtrWithCptUse<T2> &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }
    
    ~PtrWithCptUse() {
        if ( p and --p->cpt_use <= 0 )
            delete p;
    }
    
    PtrWithCptUse &operator=( T *v ) {
        if ( v )
            ++v->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v;
        return *this;
    }
    
    PtrWithCptUse &operator=( const PtrWithCptUse &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    template<class T2>
    PtrWithCptUse &operator=( const PtrWithCptUse<T2> &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    const T *ptr() const { return p; }
    T *ptr() { return p; }
    
    const T *operator->() const { return p; }
    T *operator->() { return p; }

    const T *operator*() const { return p; }
    T *operator*() { return p; }

    operator bool() const { return p; }
    
    void write_to_stream( class Stream &os ) const { os << p; }
    
    T *p;
};

template<class T>
class ConstPtrWithCptUse {
public:
    ConstPtrWithCptUse() : p( 0 ) { }
    
    ConstPtrWithCptUse( const T *v ) : p( v ) { if ( v ) ++v->cpt_use; }
    ConstPtrWithCptUse( const ConstPtrWithCptUse &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }
    ConstPtrWithCptUse( const PtrWithCptUse<T> &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }
    
    template<class T2>
    ConstPtrWithCptUse( const ConstPtrWithCptUse<T2> &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }
    
    template<class T2>
    ConstPtrWithCptUse( const PtrWithCptUse<T2> &v ) : p( v.p ) { if ( p ) ++p->cpt_use; }
    
    ~ConstPtrWithCptUse() {
        if ( p and --p->cpt_use <= 0 )
            delete p;
    }
    
    ConstPtrWithCptUse &operator=( const T *v ) {
        if ( v )
            ++v->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v;
        return *this;
    }
    
    ConstPtrWithCptUse &operator=( const ConstPtrWithCptUse &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    ConstPtrWithCptUse &operator=( const PtrWithCptUse<T> &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    template<class T2>
    ConstPtrWithCptUse &operator=( const ConstPtrWithCptUse<T2> &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    template<class T2>
    ConstPtrWithCptUse &operator=( const PtrWithCptUse<T2> &v ) {
        if ( v.p )
            ++v.p->cpt_use;
        if ( p and --p->cpt_use <= 0 )
            delete p;
        p = v.p;
        return *this;
    }
    
    const T *ptr() const { return p; }
    
    const T *operator->() const { return p; }

    const T &operator*() const { return *p; }

    operator bool() const { return p; }
    
    void write_to_stream( class Stream &os ) const { os << p; }
    
    const T *p;
};

/**

*/
class ObjectWithCptUse {
public:
    ObjectWithCptUse() : cpt_use( 0 ) {}
    mutable int cpt_use;
};


}


#endif // METIL_PtrWithCptUse_H
