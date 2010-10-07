#include "TypeConstructor_Flt.h"
#include "DisplayFlt.h"

BEG_METIL_LEVEL1_NAMESPACE;

// template<int len_mant, int len_expo, int off_mant, int off_sign, int off_expo, int bia_expo>
void metil_def_self_append__when__a__isa__String__and__b__is__Flt_64__pert__1000( MO &a, MO b ) {
    // DEFI_FLT( Fp, 64, 11, -1023  );
    DisplayFlt< 64-1-11, 11, 0, 63, 63 - 11, -1023 >::display( static_cast<String &>( a ), (const PI8 *)b.data );
}

END_METIL_LEVEL1_NAMESPACE;
