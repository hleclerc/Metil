#include "StructCompactor.h"

BEG_METIL_NAMESPACE;

void StructCompactor::ItemSca::make_decl( String &os, const String &sp ) {
}

void StructCompactor::ItemStr::make_decl( String &os, const String &sp ) {
    String np = sp + "    ";
    String op = np + "    ";
    String pp = op + "    ";
    os << sp << "struct " << type << " {\n";
    os << sp << "    typedef void HasOffPtr;\n";

    // declarations
    BasicVec<String> decl_types;
    for( int i = 0; i < items.size(); ++i ) {
        Item *bs = items[ i ]->base_str();
        if ( not decl_types.contains( bs->type ) ) {
            bs->make_decl( os, np );
            decl_types << bs->type;
        }
    }

    // methods
    os << np << "template<class T> static " << type << " *copy( MemoryDriver &md, const T *src, ST num = 1 ) {\n";
    os << np << "    " << type << " *dst, *loc;\n";
    os << np << "    ST rese = num * sizeof( " << type << " );\n";
    os << np << "    md.beg_local_data( &dst, &loc, rese, " << alig() << " );\n";
    os << np << "    for( ST i = 0; i < num; ++i ) {\n";
    int num_var = 0;
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->copy_attr( os, pp, "loc[ i ]", "src[ i ]", 1, num_var );
    os << np << "    }\n";
    os << np << "    md.end_local_data( dst, loc, rese );\n";
    os << np << "    return dst;\n";
    os << np << "}\n";

    // attributes
    for( int i = 0; i < items.size(); ++i )
        os << np << items[ i ]->type << ' ' << items[ i ]->name << ";\n";

    os << sp << "};\n";
}

void StructCompactor::ItemVec::make_decl( String &os, const String &sp ) {
}


void StructCompactor::ItemSca::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    os << sp << dst << '.' << name << " = " << src << '.' << name << ";\n";
}

void StructCompactor::ItemStr::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    String vdst; vdst << dst << '.' << name;
    String vsrc; vsrc << src << '.' << name;
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->copy_attr( os, sp, vdst, vsrc, par_level, num_var );
}

void StructCompactor::ItemVec::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    os << sp << dst << '.' << name << ".size_ = " << src << '.' << name << ".size();\n";
    os << sp << dst << '.' << name << ".rese_ = " << src << '.' << name << ".size();\n";
    data_type->copy_data( os, sp, dst + '.' + name, src + '.' + name, par_level, num_var );
}

void StructCompactor::ItemSca::copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    os << sp << "md.copy( &" << dst << ".data_, " << src << ".ptr(), " << src << ".size() * sizeof( " << type << " ), " << alig() << " );\n";
}

void StructCompactor::ItemStr::copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    os << sp << dst << ".data_ = " << type << "::copy( md, " << src << ".ptr(), " << src << ".size() );\n";
}

void StructCompactor::ItemVec::copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level, int &num_var ) {
    // make_copy( os, sp, dst, src, src + ".size()", par_level + 1 );
    int loc_num = num_var++;
    String loc; loc << "loc_" << loc_num;
    os << sp << type << " *loc_" << loc_num << ";\n";
    os << sp << "ST rese_" << loc_num << " = " << src << ".size() * sizeof( " << type << " );\n";
    os << sp << "md.beg_local_data( &" << dst << ".data_, &" << loc << ", rese_" << loc_num << ", " << alig() << " );\n";
    String i = char( 'i' + par_level );
    os << sp << "for( ST " << i << " = 0; " << i << " < " << src << ".size(); ++" << i << " ) {\n";
    os << sp << "    " << loc << "[ " << i << " ].size_ = " << src << "[ " + i + " ].size();\n";
    os << sp << "    " << loc << "[ " << i << " ].rese_ = " << src << "[ " + i + " ].size();\n";
    data_type->copy_data( os, sp + "    ", loc + "[ " + i + " ]", src + "[ " + i + " ]", par_level + 1, num_var );
    os << sp << "}\n";
    os << sp << "md.end_local_data( " << dst << ".data_, loc_" << loc_num << ", rese_" << loc_num << ");\n";
}

void StructCompactor::make_files() {
    File fh( item->type + ".h", "w" );
    fh << "#ifndef " << item->type << "_H\n";
    fh << "#define " << item->type << "_H\n";
    fh << "\n";
    fh << "#include <MemoryDriver.h>\n";
    fh << "#include <BasicVecRef.h>\n";
    fh << "\n";
    fh << "BEG_METIL_NAMESPACE\n";
    fh << "\n";
    item->make_decl( fh );
    fh << "\n";
    fh << "END_METIL_NAMESPACE\n";
    fh << "\n";
    fh << "#endif // " << item->type << "_H\n";

    File fc( item->type + ".cu", "w" );
    // item->make_defi( fc );
    fc << "#include <CudaMetil.h>\n";
    fc << "void f() {}\n";
}

END_METIL_NAMESPACE;
