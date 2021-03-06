#ifndef MO_H
#define MO_H

#include "MachineId.h"

BEG_METIL_NAMESPACE;
class String;
END_METIL_NAMESPACE;

BEG_METIL_LEVEL1_NAMESPACE;
class Type;

/**
  @brief Metil Object : contains a pointer on type and data
*/
class MO {
public:
    MO() {}
    MO( Type *type ) : type(  type ) {}
    MO( void *data, Type *type ) : data( data ), type(  type ) {}

    void operator=( MO obj ) { data = obj.data; type = obj.type; }

    ST size_in_mem() const;

    void write_str( String &os ) const;
    void write_dot( String &os, bool want_parents = false ) const;
    void write_tex( String &os ) const;

    void display_dot( const String &base_filename, bool want_parents = false ) const;
    void display_tex( const String &base_filename ) const;

    void display_dot( bool want_parents = false ) const;
    void display_tex() const;

    const MachineId *machine_id() const;

    void exec(); ///< if LazyObject, replace *this by the result of the operation. Else, do nothing

    void *data;
    Type *type;
};

extern SI64 current_MO_op_id; /// @see Owcp::op_id...

struct MetilException {};

END_METIL_LEVEL1_NAMESPACE

#endif // MO_H
