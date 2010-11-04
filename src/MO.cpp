#include "Level1/TypeConstructor.h"
#include "Level1/Owcp.h"
#include "System.h"

BEG_METIL_LEVEL1_NAMESPACE;

SI64 current_op_id = 0;

void MO::write_str( String &os ) const {
    CM_2( self_append, os, *this );
}

static void *obj_dot_ptr( const MO &obj ) {
    ST size_in_mem = obj.type->constructor->static_size_in_bytes();
    return ( size_in_mem > 0 ? obj.data : obj.type );
}

void write_dot_rec( String &os, const MO &obj, bool want_parents ) {
    if ( obj.type->cur_op_id( obj ) )
        return;

    os << "    node" << obj_dot_ptr( obj ) << " [label=\"";
    //obj.type->write_dot( obj, os );
    os << obj;
    os << "\"];\n";

    for(ST i=0;i<obj.type->nb_children( obj );++i) {
        MO ch = obj.type->get_child( obj, i );
        os << "    node" << obj_dot_ptr( obj ) << " -> node" << obj_dot_ptr( ch ) << ";\n";
        write_dot_rec( os, ch, want_parents );
    }

    if ( want_parents )
        for( OwcpChild *p = CM_1( get_parent, obj ); p; p = p->next )
            os << "    node" << obj_dot_ptr( p->self ) << " -> node" << obj_dot_ptr( obj ) << " [color=red];\n";
}

void MO::write_dot( String &os, bool want_parents ) const {
    ++current_op_id;
    write_dot_rec( os, *this, want_parents );
}

void MO::write_tex( String &/*os*/ ) const {
    TODO;
}

void MO::display_dot( const String &base_filename, bool want_parents ) const {
    String dot_file = base_filename + ".dot";
    File fout( dot_file, "w" );
    fout << "digraph my_graph {\n";
    fout << "    ordering = \"out\"\n";
    write_dot( fout, want_parents );
    fout << "};\n";
    fout.flush();

    exec_cmd( "dot -Tpdf " + base_filename + ".dot > " + base_filename + ".pdf && okular " + base_filename + ".pdf" );
}

void MO::display_tex( const String &base_filename ) const {
    File f( base_filename + ".tex", "w" );
    f << "\\documentclass{article}\n";
    f << "\\usepackage[latin1]{inputenc}\n";
    f << "\\usepackage{graphicx}\n";
    f << "\\usepackage{amsmath}\n";
    f << "\\begin{document}\n";
    f << "\\pagestyle{empty}\n";

    write_tex( f );

    f << "\\end{document}\n";

    f.close();

    if ( exec_cmd( "latex --interaction=nonstopmode " + base_filename + ".tex > /dev/null 2> /dev/null" ) )
        return;
    if ( exec_cmd( "dvips -O0in,11in -E -o " + base_filename + ".eps " + base_filename + " > /dev/null 2> /dev/null" ) )
        return;
    if ( exec_cmd( "okular " + base_filename + ".eps > /dev/null 2> /dev/null" ) )
        return;
}

void MO::display_dot( bool want_parents ) const {
    display_dot( "tmp", want_parents );
}

void MO::display_tex() const {
    display_dot( "tmp" );
}

END_METIL_LEVEL1_NAMESPACE
