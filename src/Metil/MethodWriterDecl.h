    if ( type == "Vo" ) return "void " + def_name + "( MO &a )";
    if ( type == "OO" ) return "MO " + def_name + "( MO a )";
    if ( type == "BO" ) return "bool " + def_name + "( MO a )";
    if ( type == "IO" ) return "SI32 " + def_name + "( MO a )";
    if ( type == "LO" ) return "SI64 " + def_name + "( MO a )";
    if ( type == "SO" ) return "ST " + def_name + "( MO a )";
    if ( type == "FO" ) return "FP32 " + def_name + "( MO a )";
    if ( type == "DO" ) return "FP64 " + def_name + "( MO a )";
    if ( type == "EO" ) return "FP80 " + def_name + "( MO a )";
    if ( type == "VOt" ) return "void " + def_name + "( MO a, String &b )";
    if ( type == "pO" ) return "void *" + def_name + "( MO a )";
    if ( type == "Vot" ) return "void " + def_name + "( MO &a, String &b )";
    if ( type == "po" ) return "void *" + def_name + "( MO &a )";
    if ( type == "VoPS" ) return "void " + def_name + "( MO &a, const void *b, ST c )";
    if ( type == "VOpS" ) return "void " + def_name + "( MO a, void *b, ST c )";
    if ( type == "OOO" ) return "MO " + def_name + "( MO a, MO b )";
    if ( type == "BOO" ) return "bool " + def_name + "( MO a, MO b )";
    if ( type == "VoO" ) return "void " + def_name + "( MO &a, MO b )";
    if ( type == "OoO" ) return "MO " + def_name + "( MO &a, MO b )";
    if ( type == "OOS" ) return "MO " + def_name + "( MO a, ST b )";
    if ( type == "VoY" ) return "void " + def_name + "( MO &a, struct OwcpChild *b )";
