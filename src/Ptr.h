#ifndef PTR_H
#define PTR_H

#include "Malloc.h"

BEG_METIL_NAMESPACE;

/**
  Objects pointed by Ptr<...> should inherit from ObjectWithCptUse.

  Use NEW( ... ) to allocate objects
*/
struct ObjectWithCptUse {
    ObjectWithCptUse() : cpt_use( 0 ) {}

    mutable int cpt_use;
};

template<class T>
struct ConstPtr;

/**
  Can be used for reference couting.

  T should be an object which inherits from ObjectWithCptUse.

  In the folowing example, the memory is automatically managed (the Toto object will be deleted at the end of foo)

@code
// not a reference to the famous japanese brand
struct Toto : public ObjectWithCptUse {
    ...
};

void foo() {
    Ptr<Toto> a = NEW( Toto );
    Ptr<Toto> b = a;
    b->...;
}
@endcode
*/
template<class T>
struct Ptr {
    Ptr() : data( 0 ) {}
    Ptr( T *obj ) : data( obj ) {}
    Ptr( const Ptr<T> &obj ) : data( obj.data ) { if ( data ) ++data->cpt_use; }

    ~Ptr() {
        if ( data and --data->cpt_use < 0 )
            DEL( data );
    }

    Ptr &operator=( const Ptr<T> &obj ) {
        if ( obj.data )
            ++obj.data->cpt_use;
        if ( data and --data->cpt_use < 0 )
            DEL( data );
        data = obj.data;
        return *this;
    }

    operator bool() const { return data; }

    bool operator==( const T           *p ) const { return data == p;      }
    bool operator==( const Ptr<T>      &p ) const { return data == p.data; }
    bool operator==( const ConstPtr<T> &p ) const { return data == p.data; }

    const T *ptr() const { return data; }
    T *ptr() { return data; }

    const T *operator->() const { return data; }
    T *operator->() { return data; }

    const T &operator*() const { return *data; }
    T &operator*() { return *data; }

    T *data;
};

template<class T>
struct ConstPtr {
    ConstPtr() : data( 0 ) {}
    ConstPtr( const T *obj ) : data( obj ) {}
    ConstPtr( const Ptr<T> &obj ) : data( obj.data ) { if ( data ) ++data->cpt_use; }
    ConstPtr( const ConstPtr<T> &obj ) : data( obj.data ) { if ( data ) ++data->cpt_use; }

    ~ConstPtr() {
        if ( data and --data->cpt_use < 0 )
            DEL( data );
    }

    ConstPtr &operator=( const ConstPtr<T> &obj ) {
        if ( obj.data )
            ++obj.data->cpt_use;
        if ( data and --data->cpt_use < 0 )
            DEL( data );
        data = obj.data;
        return *this;
    }

    ConstPtr &operator=( const Ptr<T> &obj ) {
        if ( obj.data )
            ++obj.data->cpt_use;
        if ( data and --data->cpt_use < 0 )
            DEL( data );
        data = obj.data;
        return *this;
    }

    operator bool() const { return data; }

    bool operator==( const T           *p ) const { return data == p;      }
    bool operator==( const Ptr<T>      &p ) const { return data == p.data; }
    bool operator==( const ConstPtr<T> &p ) const { return data == p.data; }

    const T *ptr() const { return data; }

    const T *operator->() const { return data; }

    const T &operator*() const { return *data; }

    const T *data;
};

END_METIL_NAMESPACE

#endif // PTR_H
