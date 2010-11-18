#include "Array.h"

#ifndef VEC_H
#define VEC_H

BEG_METIL_NAMESPACE;

/**
  Array of Val (i.e. scalars)

  @todo use ValRef in constructors
*/
class Vec : public Array<Val> {
public:
    Vec();
    Vec( const Vec &a ) : Array<Val>( static_cast<const Array<Val> &>( a ) ) {  }

    Vec( const Val &v_0 );
    Vec( const Val &v_0, const Val &v_1 );
    Vec( const Val &v_0, const Val &v_1, const Val &v_2 );
    Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3 );
    Vec( const Val &v_0, const Val &v_1, const Val &v_2, const Val &v_3, const Val &v_4 );

    //    template<class T,class T0> Vec( S<T> s, const T0 &v_0 ) {
    //        //Level1::MO tmp = Level1::type_ptr( s );
    //        // T *v = reinterpret_cast<T *>( init_dyn_vec( , 1 ) );
    //        // new( v + 0 ) T( v_0 );
    //    }

    template<class T,class T0,class T1> Vec( S<T> s, const T0 &v_0, const T1 &v_1 ) {
        type = Level1::type_ptr( s );
        T *v = reinterpret_cast<T *>( CM_2( allocate_vec, *this, two ) );
        new( v + 0 ) T( v_0 );
        new( v + 1 ) T( v_1 );
    }

//    template<class T,class T0,class T1,class T2> Vec( S<T> s, const T0 &v_0, const T1 &v_1, const T2 &v_2 ) {
//        T *v = reinterpret_cast<T *>( init_dyn_vec( Level1::type_ptr( s ), 3 ) );
//        new( v + 0 ) T( v_0 );
//        new( v + 1 ) T( v_1 );
//        new( v + 2 ) T( v_2 );
//    }

//    template<class T,class T0,class T1,class T2,class T3> Vec( S<T> s, const T0 &v_0, const T1 &v_1, const T2 &v_2, const T3 &v_3 ) {
//        T *v = reinterpret_cast<T *>( init_dyn_vec( Level1::type_ptr( s ), 4 ) );
//        new( v + 0 ) T( v_0 );
//        new( v + 1 ) T( v_1 );
//        new( v + 2 ) T( v_2 );
//        new( v + 3 ) T( v_3 );
//    }

//    template<class T,class T0,class T1,class T2,class T3,class T4> Vec( S<T> s, const T0 &v_0, const T1 &v_1, const T2 &v_2, const T3 &v_3, const T4 &v_4 ) {
//        T *v = reinterpret_cast<T *>( init_dyn_vec( Level1::type_ptr( s ), 5 ) );
//        new( v + 0 ) T( v_0 );
//        new( v + 1 ) T( v_1 );
//        new( v + 2 ) T( v_2 );
//        new( v + 3 ) T( v_3 );
//        new( v + 4 ) T( v_4 );
//    }

    // Vec( Level1::Type *item_type, ST size, const MachineId *machine_id = MachineId::cur() );
    Vec( Size, ST size );

    Vec &operator=( const Array<Val> &a ) { CM_2( reassign, *this, a ); return *this; }
    Vec &operator=( const Vec &a ) { CM_2( reassign, *this, a ); return *this; }

protected:
    friend class Array<Val>;
    Vec( Level1::MO mo ) : Array<Val>( mo ) {}

    Level1::MO *init_dyn_vec( Level1::Type *type, ST size );
    Level1::MO *init_dyn_vec( ST size );
};

END_METIL_NAMESPACE;

#endif // VEC_H
