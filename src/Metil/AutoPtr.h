#ifndef AUTOPTR_H
#define AUTOPTR_H

template<class T>
struct AutoPtr {
    AutoPtr() : data( 0 ) {}
    AutoPtr( T *obj ) : data( obj ) {}
    AutoPtr( const AutoPtr &obj ) { ERROR( "forbidden" ); }

    template<class U>
    AutoPtr( const AutoPtr<U> &obj ) { ERROR( "forbidden" ); }

    ~AutoPtr() {
        if ( data )
            DEL( data );
    }

    AutoPtr &operator=( const AutoPtr &obj ) {
        ERROR( "forbidden" );
        return *this;
    }

    template<class U>
    AutoPtr &operator=( const AutoPtr<U> &obj ) {
        ERROR( "forbidden" );
        return *this;
    }

    operator bool() const { return data; }

    bool operator==( const T           *p ) const { return data == p;      }
    bool operator==( const AutoPtr<T>  &p ) const { return data == p.data; }

    const T *ptr() const { return data; }
    T *ptr() { return data; }

    const T *operator->() const { return data; }
    T *operator->() { return data; }

    const T &operator*() const { return *data; }
    T &operator*() { return *data; }

    template<class Os>
    void write_str( Os &os ) const { os << data; }

    T *data;
};

#endif // AUTOPTR_H
