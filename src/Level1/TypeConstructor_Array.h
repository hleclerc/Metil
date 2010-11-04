#ifndef TYPECONSTRUCTOR_ARRAY_H
#define TYPECONSTRUCTOR_ARRAY_H

#include "TypeConstructor.h"
#include "BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  name -> contains
    - (len type)type
    - dim
    - size[ 0 ]
    - rese[ 0 ]
    - ...
    - size[ n ]
    - rese[ n ]
    - [CptUse]
    - [ExtPtr]
*/
class TypeConstructor_Array : public TypeConstructor {
public:
    virtual void init( Type *type );
    virtual void default_mw( MethodWriter &mw ) const;

    virtual int static_size_in_bits() const;
    virtual int tensor_order() const;
    virtual int needed_alignement_in_bits() const;
    virtual void write_select_op( MethodWriter &mw, const Mos *a, TypeConstructor *index_type, const String &op ) const;

    DECL_WRITER( del );
    DECL_WRITER( size );
    DECL_WRITER( sizes );

    int  dim() const;
    bool dyn() const; ///< true if dynamic
    int  len() const; ///< nb items
    int  len_size() const; ///< nb items of size that are < 0 (i.e. not defined by the type but by the data)
    int  len_rese() const; ///< nb items of rese that are < 0 (i.e. not defined by the type but by the data)

    void write_get_header  ( MethodWriter &cw, const String &name_header, const String &name_data ) const;
    void write_get_data_ptr( MethodWriter &cw, bool want_const, const String &name_data = "d", const String &name_header = "h", const String &data = "toto" ) const;
    void write_get_len     ( MethodWriter &cw, const String &name_res, const String &name_header = "h" ) const;
    void write_get_index   ( MethodWriter &cw, const String &name_res, const TypeConstructor *c_1, const Mos &d_1, const String &name_header = "h" ) const;
    void write_beg_loop    ( MethodWriter &cw, const String &name_header, int d ) const;
    void write_end_loop    ( MethodWriter &cw, const String &name_header, int d, const String &ptr_on_data = "", const String &inc = "1" ) const;
    void write_add_ptrd    ( MethodWriter &cw, const String &name_header, const String &name_data, int d ) const;

    String get_size_n( const String &name_header, int d ) const;
    String get_rese_n( const String &name_header, int d ) const;

    BasicVec<ST> size;
    BasicVec<ST> rese;
    bool want_CptUse;
    bool want_ExtPtr;
    Type *item_type_bas;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_ARRAY_H
