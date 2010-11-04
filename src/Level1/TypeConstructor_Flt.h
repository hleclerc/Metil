#ifndef TYPECONSTRUCTOR_FLT_H
#define TYPECONSTRUCTOR_FLT_H

#include "MethodWriterHelper_Int.h"
#include "TypeConstructor.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
    name ->
      Flt_ off_mant _ len_mant _ off_expo _ len_expo _ off_sign _ len_sign _ bia_expo
*/
class TypeConstructor_Flt : public TypeConstructor {
public:
    virtual void init( Type *type );
    virtual int static_size_in_bits() const;
    virtual bool is_a_POD() const;
    virtual String cpp_type() const;

    DECL_WRITER( write_str );

    MethodWriterHelper_Int mant;
    MethodWriterHelper_Int expo;
    MethodWriterHelper_Int sign;
    int bia_expo;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_FLT_H
