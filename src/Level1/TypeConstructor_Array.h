#ifndef TYPECONSTRUCTOR_ARRAY_H
#define TYPECONSTRUCTOR_ARRAY_H

#include "TypeConstructor.h"
#include "../BasicVec.h"

BEG_METIL_LEVEL1_NAMESPACE;

/**
  name contains
    - (len type)type
    - dim
    - size[ 0 ]
    - rese[ 0 ]
    - ...
    - size[ n ]
    - rese[ n ]
    - [CptUse]
    - [ExtPtr]
    - [Gpu]
    - [MachineId]
*/
class TypeConstructor_Array : public TypeConstructor {
public:
    virtual void init( Type *type );
    virtual void default_mw( MethodWriter &mw ) const;

    virtual int static_size_in_bits() const;
    virtual int tensor_order() const;
    virtual int needed_alignement_in_bits() const;
    virtual void write_select_op( MethodWriter &mw, TypeConstructor *index_type, const String &op ) const;

    DECL_WRITER( del );
    DECL_WRITER( init );
    DECL_WRITER( copy );
    DECL_WRITER( size );
    DECL_WRITER( sizes );
    DECL_WRITER( write_str );
    DECL_WRITER( machine_id );
    DECL_WRITER( size_in_mem );
    DECL_WRITER( mul_1 );


    int  dim() const;
    bool dyn() const; ///< true if dynamic
    int  len() const; ///< nb items
    int  len_size() const; ///< nb items of size that are < 0 (i.e. not defined by the type but by the data)
    int  len_rese() const; ///< nb items of rese that are < 0 (i.e. not defined by the type but by the data)
    bool need_header() const; ///< true if needs a header

    void write_get_t_header( MethodWriter &cw, const String &name_type ) const; ///< typedef for header
    void write_get_static_s( MethodWriter &cw, const String &res ) const; ///< static size in a variable
    void write_get_header  ( MethodWriter &cw, const String &name_header, const String &name_data, const String &name_type = "AH" ) const;
    void write_get_data_ptr( MethodWriter &cw, bool want_const, const String &name_data = "d", const String &name_header = "h", const String &data = "toto" ) const;
    void write_get_len     ( MethodWriter &cw, const String &name_res, const String &name_header = "h" ) const;
    void write_get_index   ( MethodWriter &cw, const String &name_res, const TypeConstructor *c_1, const Mos &d_1, const String &name_header = "h" ) const;
    void write_beg_loop    ( MethodWriter &cw, const String &name_header, int d ) const;
    void write_end_loop    ( MethodWriter &cw, const String &name_header, int d, const String &ptr_on_data = "", const String &inc = "1" ) const;
    void write_smp_beg_loop( MethodWriter &cw, const String &data, bool want_const ) const; ///< simple beg loop (make typedef ... AH, ... for(...) )
    void write_smp_end_loop( MethodWriter &cw ) const; ///< simple end loop
    void write_add_ptrd    ( MethodWriter &cw, const String &name_header, const String &name_data, int d ) const;

    String get_size_n( const String &name_header, int d ) const;
    String get_rese_n( const String &name_header, int d ) const;

    BasicVec<ST> size;
    BasicVec<ST> rese;
    bool want_CptUse;
    bool want_ExtPtr;
    bool want_Gpu;
    bool want_MachineId;
    Type *item_type_bas;
};

END_METIL_LEVEL1_NAMESPACE;

#endif // TYPECONSTRUCTOR_ARRAY_H
