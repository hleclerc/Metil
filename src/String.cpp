#include "String.h"

#include <stdio.h>

BEG_METIL_NAMESPACE;

String::Endl String::endl;
String::Flsh String::flsh;

String cout( Level1::MO( stdout, &Level1::metil_type_ref_FileWithoutClose ) );
String cerr( Level1::MO( stderr, &Level1::metil_type_ref_FileWithoutClose ) );
String cin ( Level1::MO( stdin , &Level1::metil_type_ref_FileWithoutClose ) );

void String::Endl::write_str( String &os ) const { os << '\n'; os.flush(); }
void String::Flsh::write_str( String &os ) const { os.flush(); }

END_METIL_NAMESPACE;
