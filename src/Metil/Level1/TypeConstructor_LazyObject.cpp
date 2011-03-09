#include "TypeConstructor_LazyObject.h"
#include "LazyObjectOperationData.h"
#include "LazyObjectData.h"
#include "MethodFinder.h"

BEG_METIL_LEVEL1_NAMESPACE;

//static TypeConstructor_LazyObject *sc( Type *type ) {
//    return static_cast<TypeConstructor_LazyObject *>( type->constructor );
//}

/// necessary because the generator will PRINT(cmd), which ma
void metil_def_flush__when__a__isa__LazyObject( MO &a ) {
    a.exec();
    TODO;
    // reinterpret_cast<Owcp<2,LazyObjectOperationData_OOO> *>( a.data )->dec_ref();
}

// ... metil_def__...__when__a__isa__LazyObject( ... ) { return ... }
#include "def_LazyObj.h"

#define AVOID_DEL
#define AVOID_COPY
#define AVOID_LAZY_OP

#define DECL_MET( T, N ) MET_##T( N )
#include "DeclMethods.h"
#undef DECL_MET

#define DECL_MET( T, N ) MET_1_##T( N )
#include "DeclMethodsBinary.h"
#undef DECL_MET

void TypeConstructor_LazyObject::write_header( MethodWriter &mw, const String &name_header, const String &data ) const {
    String t; t<< "Owcp<" << Owcp_size() << "," << Owcp_data() << ">";
    mw.n << t << " *" << name_header << " = reinterpret_cast<" << t << " *>( " << data << " );";
}

void TypeConstructor_LazyObject::default_mw( MethodWriter &mw ) const {
    mw.add_include( "Metil/Level1/LazyObjectData.h" );
}

String TypeConstructor_LazyObject::Owcp_data() const {
    return "LazyObjectData";
}

END_METIL_LEVEL1_NAMESPACE;
