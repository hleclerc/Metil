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
    virtual int needed_alignement_in_bits_if_in_vec( MachineId::Type mid ) const;

    DECL_WRITER( convert_to_Bool );
    DECL_WRITER( convert_to_SI32 );
    DECL_WRITER( convert_to_SI64 );
    DECL_WRITER( convert_to_FP32 );
    DECL_WRITER( convert_to_FP64 );
    DECL_WRITER( convert_to_FP80 );

    DECL_WRITER( write_str );

    MethodWriterHelper_Int mant;
    MethodWriterHelper_Int expo;
    MethodWriterHelper_Int sign;
    int bia_expo;

private:
    void write_convert_to_( MethodWriter &mw ) const;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_FLT_H
