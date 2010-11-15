#include "TypeConstructor.h"
#include "MethodGenerator.h"
#include "NbArgsMethods.h"
#include "BasicMethods.h"
#include "MethodName.h"
#include "StringHelp.h"
#include "BasicVec.h"
#include "Math.h"

BEG_METIL_LEVEL1_NAMESPACE;

static int nb_types = 1;    ///< Nb types of @em instantiated objects (i.e. nb types that have been used at least one time). type number 0 is fake.
static Type *last_type = 0; ///< pointer on type list. Contains all the types, including the non instantiated ones

struct BinMethodsInfo {
    void *&ptr( int number_type_a, int num_method, int number_type_b ) {
        return data_ptr[ nb_items * nb_types * number_type_a + nb_types * num_method + number_type_b ];
    }
    ST     rese_mem; ///< total size in bytes of room reserved for arrays for binary methods. [Type * Method * Type * sizeof]
    ST     nb_types; ///< nb types that can be fitted into bin_methods_data_ptr
    void **data_ptr; ///< data for binary methods (for all methods and initialized types)
    int    nb_items; ///< card([ add, self_add, sub, ... ]) -> nb methods
};
static BinMethodsInfo bin_methods_info = { 0, 0, 0, 0 };


template<class TM,class TN>
static void init_method( Type *type, TM *&m, TN, int &num_binary_method, bool first_time ) {
    if ( first_time )
        m = MethodGenerator<TM,TN>::generator;
}

template<class TM,class TN>
static void init_method( Type *type, TM **&m, TN, int &num_binary_method, bool first_time ) {
    m = (TM **)&bin_methods_info.ptr( type->number, num_binary_method++, 0 );
}

static void init_met_ptr( Type *type, bool first_time ) {
    int num_binary_method = 0;
    #define DECL_MET( T, N ) init_method( type, type->N, MethodName_##N(), num_binary_method, first_time )
    #include "DeclMethods.h"
    #undef DECL_MET
}

template<class TN>
static void old_to_new_bin_methods_data_ptr( BinMethodsInfo &old_methods_info, int &num_binary_method, TN ) {
    for( ST t = 0; t < old_methods_info.nb_types; ++t ) {
        for( ST i = 0; i < old_methods_info.nb_types; ++i )
            bin_methods_info.ptr( t, num_binary_method, i ) = old_methods_info.ptr( t, num_binary_method, i );
        for( ST i = old_methods_info.nb_types; i < bin_methods_info.nb_types; ++i )
            bin_methods_info.ptr( t, num_binary_method, i ) = (void *)MethodGenerator<typename TN::TA,TN>::generator;
    }
    for( ST t = old_methods_info.nb_types; t < bin_methods_info.nb_types; ++t )
        for( ST i = 0; i < bin_methods_info.nb_types; ++i )
            bin_methods_info.ptr( t, num_binary_method, i ) = (void *)MethodGenerator<typename TN::TA,TN>::generator;
    ++num_binary_method;
}

static void update_bin_methods_data( int nb_types ) {
    // need to resize data for binary methods ?
    if ( bin_methods_info.nb_types < nb_types ) {
        BinMethodsInfo old_methods_info = bin_methods_info;

        // reservation
        bin_methods_info.nb_types = 2 * nb_types;
        bin_methods_info.rese_mem = bin_methods_info.nb_types * bin_methods_info.nb_types * bin_methods_info.nb_items * sizeof( void * );
        bin_methods_info.data_ptr = (void **)MALLOC( bin_methods_info.rese_mem );
        bin_methods_info.nb_types = sqrt( FP64( bin_methods_info.rese_mem / bin_methods_info.nb_items / sizeof( void * ) ) );

        // complete and copy old data
        int num_binary_method = 0;
        #define DECL_MET( T, N ) if ( NB_ARGS_METHOD_##T == 2 ) old_to_new_bin_methods_data_ptr( old_methods_info, num_binary_method, MethodName_##N() )
        #include "DeclMethods.h"
        #undef DECL_MET

        // free old_data
        if ( old_methods_info.data_ptr )
            FREE( old_methods_info.data_ptr, old_methods_info.rese_mem );

        // update type->method->ptr
        for( Type *t = last_type; t; t = t->prev_type )
            init_met_ptr( t, false );
    }
}

Type::Type( TypeConstructor *constructor, const char *name, Type *bas, Type *ref, Type *cst, BRC k ) {
    for( Type *t = last_type; t; t = t->prev_type )
        if ( t == this )
            return; // this has already been initalised during a preceding lib load

    this->number = 0;
    this->name = name;
    this->constructor = constructor;
    this->bas_type = bas;
    this->ref_type = ref;
    this->cst_type = cst;

    prev_type = last_type;
    last_type = this;

    // if we are initializing the very first type
    if ( bin_methods_info.nb_items == 0 ) {
        // compute nb binary methods
        #define DECL_MET( T, N ) bin_methods_info.nb_items += NB_ARGS_METHOD_##T == 2
        #include "DeclMethods.h"
        #undef DECL_MET
        // room for default binary methods
        update_bin_methods_data( 32 );
        //
        reg_def();
    }

    // initilization of method ptr
    init_met_ptr( this, true );

    // particular case (no need to call finder(...))
    if ( k == Ref or k == Cst ) {
        destroy = do_nothing_VO;
        free    = do_nothing_VO;
        del     = do_nothing_VO;
    }
}

Type::~Type() {
    if( prev_type == 0 and bin_methods_info.data_ptr )
        FREE( bin_methods_info.data_ptr, bin_methods_info.rese_mem );
}

Type *Type::init_if_necessary() {
    if ( number == 0 ) {
        //
        number = nb_types++;

        //
        update_bin_methods_data( nb_types );
        init_met_ptr( this, false );

        //
        if ( not constructor->have_been_initialized ) {
            constructor->init( this );
            constructor->have_been_initialized = true;
        }
    }

    return this;
}

Type *Type::dyn_array_type( int dim, MachineId *mid ) {
    return &constructor->dyn_array_type( dim, name, mid )->bas_type;
}

Type *Type::static_vec_type( ST size, MachineId *mid ) {
    return &constructor->static_vec_type( size, name, mid )->bas_type;
}

Type *Type::sta_array_type( int dim, ST *size, MachineId *mid ) {
    return &constructor->sta_array_type( dim, size, name, mid )->bas_type;
}

Type *Type::find_with_name( const char *name ) {
    for( Type *t = last_type; t; t = t->prev_type )
        if ( Level1::equal( t->name, name ) )
            return t;
    return 0;
}

END_METIL_LEVEL1_NAMESPACE;
