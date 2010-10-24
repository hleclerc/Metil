#include "Field.h"
#include "FieldItem.h"
#include "PluginFunction.h"
#include "InstallDir.h"
#include "CString.h"

namespace Metil {

Field::Field() : item( 0 ) {
}

Field::Field( const CString &filename ) : item( 0 ) {
}

Field::~Field() {
    if ( item )
        dec_ref( item );
}

} // namespace Metil

