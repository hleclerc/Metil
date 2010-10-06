#include "TypeConstructor_ConstCharPtr.h"
#include "StringHelp.h"
#include "NewAndRefNumber.h"

BEG_METIL_LEVEL1_NAMESPACE;

MO metil_def_copy__when__a__isa__ConstCharPtr( MO a ) { return a; }

MO metil_def_size__when__a__isa__ConstCharPtr( MO a ) { return NEW_Number( strlen( (const char *)a.data ) ); }

const void *metil_def_ptr_z__when__a__isa__ConstCharPtr( MO &a ) { return a.data; }

const void *metil_def_new_ptr_z__when__a__isa__ConstCharPtr( MO a ) { return strdup( (const char *)a.data ); }

void metil_def_copy_data__when__a__isa__ConstCharPtr( MO a, void *ptr, ST size ) { memcpy( ptr, a.data, size ); }

MO metil_def_equal__when__a__isa__ConstCharPtr__and__b__isa__ConstCharPtr__pert__1( MO a, MO b ) { return NEW_Number( equal( (const char *)a.data, (const char *)b.data ) ); }

END_METIL_LEVEL1_NAMESPACE;
