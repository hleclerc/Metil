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

    // copy method
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

    // update_ptr method
    os << np << "void update_ptr_cpu_load( ST off );\n";
    os << np << "void update_ptr_cpu_save( ST off );\n";
    os << np << "void update_ptr_gpu_load( ST off );\n";
    os << np << "void update_ptr_gpu_save( ST off );\n";
    os << "\n";

    // attributes
    for( int i = 0; i < items.size(); ++i )
        os << np << items[ i ]->type << ' ' << items[ i ]->name << ";\n";

    os << sp << "};\n";
}

void StructCompactor::ItemSca::make_defi( String &os, const String &pr, BasicVec<String> &already_defined ) {
}

void StructCompactor::ItemStr::make_defi( String &os, const String &pr, BasicVec<String> &already_defined ) {
    if ( already_defined.contains( pr + type ) )
        return;
    already_defined << pr + type;

    static const char *lsl[] = { "_load", "_save" };
    for( int save = 0; save < 2; ++save ) {
        const char *ls = lsl[ save ];
        for( int gpu = 0; gpu < 2; ++gpu ) {
            if ( gpu ) {
                os << "__global__\n";
                os << "void " << pr.replace( ':', '_' ) << type << "__update_ptr_gpu" << ls << "( " << pr << type << " *obj, ST off ) {\n";
            } else
                os << "void " << pr << type << "::update_ptr_cpu" << ls << "( ST off ) {\n";
            //
            for( int i = 0; i < items.size(); ++i )
                items[ i ]->make_uptr( os, ( gpu ? "obj->" : "" ) + items[ i ]->name, 0, "    ", save );

            os << "}\n";
            os << "\n";
            if ( gpu ) {
                os << "void " << pr << type << "::update_ptr_gpu" << ls << "( ST off ) {\n";
                os << "    " << pr.replace( ':', '_' ) << type << "__update_ptr_gpu" << ls << "<<<1,1>>>( this, off );\n";
                os << "}\n";
                os << "\n";
            }
        }
    }
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->make_defi( os, pr + type + "::", already_defined );
}

void StructCompactor::ItemVec::make_defi( String &os, const String &pr, BasicVec<String> &already_defined ) {
    data_type->make_defi( os, pr, already_defined );
}


void StructCompactor::ItemSca::make_uptr( String &os, const String &pr, int par_level, const String &sp, bool save ) {
}

void StructCompactor::ItemStr::make_uptr( String &os, const String &pr, int par_level, const String &sp, bool save ) {
    for( int i = 0; i < items.size(); ++i )
        items[ i ]->make_uptr( os, pr + '.' + items[ i ]->name, par_level, sp, save );
}

void StructCompactor::ItemVec::make_uptr( String &os, const String &pr, int par_level, const String &sp, bool save ) {
    if ( not save ) // load
        os << sp << "(char *&)" << pr << ".data_ += off;\n";
    data_type->make_uptv( os, pr, par_level, sp, save );
    if ( save )
        os << sp << "(char *&)" << pr << ".data_ += off;\n";
}

void StructCompactor::ItemSca::make_uptv( String &os, const String &pr, int par_level, const String &sp, bool save ) {
}

void StructCompactor::ItemStr::make_uptv( String &os, const String &pr, int par_level, const String &sp, bool save ) {
    String i = char( 'i' + par_level );
    os << sp << "for( ST " << i << " = 0; " << i << " < " << pr << ".size_; ++" << i << " ) {\n";
    for( int j = 0; j < items.size(); ++j )
        items[ j ]->make_uptr( os, pr + ".data_[ " + i + " ]." + items[ j ]->name, par_level + 1, sp + "    ", save );
    os << sp << "}\n";
}

void StructCompactor::ItemVec::make_uptv( String &os, const String &pr, int par_level, const String &sp, bool save ) {
    String i = char( 'i' + par_level );
    os << sp << "for( ST " << i << " = 0; " << i << " < " << pr << ".size_; ++" << i << " ) {\n";
    make_uptr( os, pr + ".data_[ " + i + " ]", par_level + 1, sp + "    ", save );
    os << sp << "}\n";
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
    os << sp << "md.end_local_data( " << dst << ".data_, loc_" << loc_num << ", rese_" << loc_num << " );\n";
}

void StructCompactor::make_files( const String &dir ) {
    File fh( dir + '/' + item->type + ".h", "w" );
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

    File fc( dir + '/' + item->type + ".cu", "w" );
    fc << "#include \"" << item->type << ".h\"\n";
    fc << "\n";
    fc << "BEG_METIL_NAMESPACE\n";
    fc << "\n";
    BasicVec<String> already_defined;
    item->make_defi( fc, "", already_defined );
    fc << "\n";
    fc << "END_METIL_NAMESPACE\n";
}

END_METIL_NAMESPACE;
