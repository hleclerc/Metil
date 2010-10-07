#include "StructCompactor.h"

BEG_METIL_NAMESPACE;

void StructCompactor::ItemSca::make_decl( String &os, const String &sp ) {
}

void StructCompactor::ItemStr::make_decl( String &os, const String &sp ) {
    String np = sp + "    ";
    String op = np + "    ";
    os << sp << "struct " << type << " {\n";

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
    os << np << "    " << type << " *dst;\n";
    make_copy( os, op, "dst", "src", "num", 0 );
    os << np << "    return dst;\n";
    os << np << "}\n";

    // attributes
    for( int i = 0; i < items.size(); ++i )
        os << np << items[ i ]->type << ' ' << items[ i ]->name << ";\n";

    os << sp << "};\n";
}

void StructCompactor::ItemVec::make_decl( String &os, const String &sp ) {
}

void StructCompactor::ItemSca::make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level ) {
}

void StructCompactor::ItemStr::make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level ) {
    os << sp << type << " *loc;\n";
    os << sp << "md.beg_local_data( &" << dst << ", &loc, " << num << " * sizeof( " << type << " ), " << alig() << " );\n";
    String i = char( 'i' + par_level );
    os << sp << "for( ST " << i << " = 0; " << i << " < " << num << "; ++" << i << " ) {\n";
    String vdst; vdst << dst << "[ " << i << " ]";
    String vsrc; vsrc << src << "[ " << i << " ]";
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->copy_attr( os, sp + "    ", vdst, vsrc, par_level + 1 );
    os << sp << "}\n";
    os << sp << "md.end_local_data( " << dst << ", loc, " << num << " * sizeof( " << type << " ) );\n";
}

void StructCompactor::ItemVec::make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level ) {
}

void StructCompactor::ItemSca::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level ) {
    os << sp << dst << '.' << name << " = " << src << '.' << name << ";\n";
}

void StructCompactor::ItemStr::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level ) {
    String vdst; vdst << dst << '.' << name;
    String vsrc; vsrc << dst << '.' << name;
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->copy_attr( os, sp, vdst, vsrc, par_level );
}

void StructCompactor::ItemVec::copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level ) {
    String size; size << src << '.' << name << ".size()";
    os << sp << dst << '.' << name << ".size_ = " << size << ";\n";
    os << sp << dst << '.' << name << ".rese_ = " << size << ";\n";
    data_type->make_copy( os, sp, dst + '.' + name + ".data_", src + '.' + name + ".ptr()", size, par_level );

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


//String StructCompactor::needed_alignement() const {
//    if ( type == "FP32" or type == "FP64" or type == "SI32" or type == "SI64" )
//        return "16 * 4";
//    return "sizeof( ST )";
//}

//bool StructCompactor::is_POD() const {
//    for( int i = 0; i < items.size(); ++i )
//        if ( not items[ i ]->is_POD() )
//            return 0;
//    return pointed_type == 0;
//}

//void StructCompactor::make_copy( String &os, const String &sp, const String &dst, const String &src, int par_lev ) {
//    for( int i = 0; i < items.size(); ++i ) {
//        os << sp << "// " << items[ i ]->name << " \n";
//        if ( items[ i ]->pointed_type ) {
//            String size; size << src << '.' << items[ i ]->name << ".size()";
//            String ptr ; ptr  << src << '.' << items[ i ]->name << ".ptr()";
//            os << sp << dst << '.' << items[ i ]->name << ".size_ = " << size << ";\n";
//            os << sp << dst << '.' << items[ i ]->name << ".rese_ = " << size << ";\n";
//            if ( items[ i ]->pointed_type->is_POD() ) { // Vec<POD> (e.g. Vec<FP64>)
//                os << sp << "md.copy( &" << dst << '.' << items[ i ]->name << ".data_, " << ptr << ", " << size << " * sizeof( " << items[ i ]->pointed_type->type << " ), " << items[ i ]->pointed_type->needed_alignement() << " );\n";
//            } else if ( items[ i ]->pointed_type->int_type ) { // Vec<LocalStruct>
//                os << sp << dst << '.' << items[ i ]->name << ".data_ = " << items[ i ]->pointed_type->type << "::push_copy_in( md, " << ptr << ", " << size << " );\n";
//            } else { // Vec<Vec<...> >
//                items[ i ]->pointed_type->make_push( os, sp, items[ i ]->name + ".data_", par_lev + 1, '_' + String( par_lev ), size );
//            }
//        } else {
//            if ( items[ i ]->int_type ) // recursive copy
//                items[ i ]->make_copy( os, sp, dst + '.' + items[ i ]->name, src + '.' + items[ i ]->name, par_lev );
//            else // simple attibute
//                os << sp << dst << '.' << items[ i ]->name << " = " << src << '.' << items[ i ]->name << ";\n";
//        }
//    }
//}

//void StructCompactor::make_push( String &os, const String &sp, const String &dst, int par_lev, const String &suf, const String &n ) {
//    os << sp << type << " *loc" << suf << "; ST rese" << suf << " = " << n << " * sizeof( " << type << " );\n";
//    os << sp << "md.beg_local_data( &" << dst << ", &loc" << suf << ", rese" << suf << ", " << needed_alignement() << " );\n";
//    String i = char( 'i' + par_lev );
//    os << sp << "for( ST " << i << " = 0; " << i << " < n; ++" << i << " ) {\n";
//    make_copy( os, sp + "    ", "loc" + suf + "[ " + i + " ]", "src[ " + i + " ]", par_lev );
//    os << sp << "}\n";
//    os << sp << "md.end_local_data( " << dst << ", loc" << suf << ", rese" << suf << " );\n";
//}



END_METIL_NAMESPACE;
