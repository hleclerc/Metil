#include "StructCompactor.h"

BEG_METIL_NAMESPACE;

StructCompactor *StructCompactor::base_str() {
    if ( pointed_type )
        return pointed_type->base_str();
    return this;
}

String StructCompactor::needed_alignement() const {
    if ( type == "FP32" or type == "FP64" or type == "SI32" or type == "SI64" )
        return "16 * 4";
    return "sizeof( ST )";
}

bool StructCompactor::is_POD() const {
    for( int i = 0; i < items.size(); ++i )
        if ( not items[ i ]->is_POD() )
            return 0;
    return pointed_type == 0;
}

void StructCompactor::make_copy( String &os, const String &sp, const String &dst, const String &src, int par_lev ) {
    for( int i = 0; i < items.size(); ++i ) {
        os << sp << "// " << items[ i ]->name << " \n";
        if ( items[ i ]->pointed_type ) {
            String size; size << src << '.' << items[ i ]->name << ".size()";
            String ptr ; ptr  << src << '.' << items[ i ]->name << ".ptr()";
            os << sp << dst << '.' << items[ i ]->name << ".size_ = " << size << ";\n";
            os << sp << dst << '.' << items[ i ]->name << ".rese_ = " << size << ";\n";
            if ( items[ i ]->pointed_type->is_POD() ) { // Vec<POD> (e.g. Vec<FP64>)
                os << sp << "md.copy( &" << dst << '.' << items[ i ]->name << ".data_, " << ptr << ", " << size << " * sizeof( " << items[ i ]->pointed_type->type << " ), " << items[ i ]->pointed_type->needed_alignement() << " );\n";
            } else if ( items[ i ]->pointed_type->int_type ) { // Vec<LocalStruct>
                os << sp << dst << '.' << items[ i ]->name << ".data_ = " << items[ i ]->pointed_type->type << "::push_copy_in( md, " << ptr << ", " << size << " );\n";
            } else { // Vec<Vec<...> >
                items[ i ]->pointed_type->make_push( os, sp, items[ i ]->name + ".data_", par_lev + 1, '_' + String( par_lev ), size );
            }
        } else {
            if ( items[ i ]->int_type ) // recursive copy
                items[ i ]->make_copy( os, sp, dst + '.' + items[ i ]->name, src + '.' + items[ i ]->name, par_lev );
            else // simple attibute
                os << sp << dst << '.' << items[ i ]->name << " = " << src << '.' << items[ i ]->name << ";\n";
        }
    }
}

void StructCompactor::make_push( String &os, const String &sp, const String &dst, int par_lev, const String &suf, const String &n ) {
    os << sp << type << " *loc" << suf << "; ST rese" << suf << " = " << n << " * sizeof( " << type << " );\n";
    os << sp << "md.beg_local_data( &" << dst << ", &loc" << suf << ", rese" << suf << ", " << needed_alignement() << " );\n";
    String i = char( 'i' + par_lev );
    os << sp << "for( ST " << i << " = 0; " << i << " < n; ++" << i << " ) {\n";
    make_copy( os, sp + "    ", "loc" + suf + "[ " + i + " ]", "src[ " + i + " ]", par_lev );
    os << sp << "}\n";
    os << sp << "md.end_local_data( " << dst << ", loc" << suf << ", rese" << suf << " );\n";
}

void StructCompactor::make_decl( String &os, const String &sp ) {
    os << sp << "struct " << type << " {\n";
    String np = sp + "    ";
    String op = np + "    ";

    // types
    BasicVec<String> decl_types;
    for( int i = 0; i < items.size(); ++i ) {
        StructCompactor *bs = items[ i ]->base_str();
        if ( bs->int_type and not decl_types.contains( bs->type ) ) {
            decl_types << bs->type;
            bs->make_decl( os, np );
        }
    }

    // copy
    os << np << "template<class T> static " << type << " *push_copy_in( MemoryDriver &md, const T *src, ST n = 1 ) {\n";
    os << np << "    " << type << " *dst;\n";
    make_push( os, op, "dst" );
    os << np << "    return dst;\n";
    os << np << "}\n";

    // attributes
    for( int i = 0; i < items.size(); ++i )
        os << np << items[ i ]->type << ' ' << items[ i ]->name << ";\n";

    os << sp << "};\n";
}

void StructCompactor::make_defi( String &os, const String &sp ) {
    os << "#include <CudaMetil.h>\n";
    os << "void f() {}\n";
}

void StructCompactor::make_file() {
    File fh( type + ".h", "w" );
    fh << "#ifndef " << type << "_H\n";
    fh << "#define " << type << "_H\n";
    fh << "\n";
    fh << "#include <MemoryDriver.h>\n";
    fh << "#include <BasicVecRef.h>\n";
    fh << "\n";
    fh << "BEG_METIL_NAMESPACE\n";
    fh << "\n";
    make_decl( fh );
    fh << "\n";
    fh << "END_METIL_NAMESPACE\n";
    fh << "\n";
    fh << "#endif // " << type << "_H\n";

    File fc( type + ".cu", "w" );
    make_defi( fc );
}


END_METIL_NAMESPACE;
