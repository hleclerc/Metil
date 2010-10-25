#ifndef INCANDDECREF_H
#define INCANDDECREF_H

namespace Metil {

///
template<class T>
inline void dec_ref( const T *op ) {
    if ( --op->cpt_use + op->parents.size() <= 0 )
        delete op;
}


///
template<class T>
inline const T *inc_ref( const T *v ) {
    ++v->cpt_use;
    return v;
}

///
template<class T>
struct AutoDecRef {
    AutoDecRef( const T *op ) : op( op ) {}
    ~AutoDecRef() { dec_ref( op ); }

    const T *operator->() { return op; }

    const T *op;
};

} // namespace Metil

#endif // INCANDDECREF_H
