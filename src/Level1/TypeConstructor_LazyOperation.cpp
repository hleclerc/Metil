#include "TypeConstructor_LazyOperation.h"
#include "LazyObjectOperationData.h"
#include "NbArgsMethods.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

/// necessary because the generator will PRINT(cmd), which ma
void metil_def_del__when__a__is__LazyOperation_append__pert__100( MO &a ) {
    reinterpret_cast<Owcp<2,LazyObjectOperationData_OOO> *>( a.data )->dec_ref();
}

int TypeConstructor_LazyOperation::Owcp_size() const {
    return nb_args;
}

String TypeConstructor_LazyOperation::Owcp_data() const {
    return "LazyObjectOperationData_" + type_operation;
}

void TypeConstructor_LazyOperation::default_mw( MethodWriter &mw ) {
    TypeConstructor_LazyObject::default_mw( mw );
    mw.add_include( "Level1/LazyObjectOperationData.h" );
}


void TypeConstructor_LazyOperation::init( Type *type ) {
    name_operation = type->name + 14; /// LazyOperation_

    // nb_args = ;
    nb_args = -1;
    #define DECL_MET( T, N ) if ( name_operation == #N ) { nb_args = NB_ARGS_METHOD_##T; type_operation = #T; }
    #include "DeclMethods.h"
    #undef DECL_MET
    ASSERT( nb_args >= 0, "unknown operation name %s", name_operation.c_str() );
}


END_METIL_LEVEL1_NAMESPACE;
