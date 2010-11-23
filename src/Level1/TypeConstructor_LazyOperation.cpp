#include "TypeConstructor_LazyOperation.h"
#include "NbArgsMethods.h"

BEG_METIL_LEVEL1_NAMESPACE;

int TypeConstructor_LazyOperation::Owcp_size() const {
    return nb_args;
}

String TypeConstructor_LazyOperation::Owcp_data() const {
    return "LazyObjectOperationData_" + type_operation;
}

void TypeConstructor_LazyOperation::default_mw( MethodWriter &mw ) {
    TypeConstructor_LazyObject::default_mw( mw );
    mw.add_include( "Level1/def_LazyObj.h" );
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
