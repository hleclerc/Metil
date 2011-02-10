#ifndef SYMBOLHEADER_H
#define SYMBOLHEADER_H

#include "../String.h"
#include "Owcp.h"

BEG_METIL_LEVEL1_NAMESPACE;

struct SymbolHeaderData {
    CANNOT_BE_DERIVED;

    String cpp;
    String tex;
};

/**
  Data for symbols
*/
struct SymbolHeader : public OwcpWithoutChild<SymbolHeaderData> {
    SymbolHeader( const String &cpp ) {
        new( &data.cpp ) String( cpp );
        new( &data.tex ) String( cpp );
        //data.cpp = cpp;
        //data.tex = cpp;
    }
    SymbolHeader( const String &cpp, const String &tex ) {
        new( &data.cpp ) String( cpp );
        new( &data.tex ) String( tex );
        //data.cpp = cpp;
        //data.tex = tex;
    }
};

END_METIL_LEVEL1_NAMESPACE;

#endif // SYMBOLHEADER_H
