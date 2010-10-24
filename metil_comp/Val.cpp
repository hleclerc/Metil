/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "Val.h"
#include "ValItem.h"
#include "System.h"
#include "BasicVec.h"

namespace Metil {

Val::Val() : op( inc_ref( number_0 ) ) {}

Val::Val( const ValItem *op ) : op( op ) {}

Val::Val( const CString &nb, int base ) {
    int i = nb.rfind('/');
    if ( i >= 0 ) {
        op = new_number(
                BigInt( CString( nb.data()    , nb.data()+i         ) ),
                BigInt( CString( nb.data()+i+1, nb.data()+nb.size() ) )
        );
    } else
        op = new_number( BigInt( nb ) );
}

//Val::Val( const CString &cpp, const CString &tex ) : op( new_symbol( cpp, tex ) ) {}
Val::Val( const CString &cpp, const CString &tex ) {
    if (cpp != "pi")    
        op = new_symbol( cpp, tex );
    else
        op = inc_ref( number_pi ); 
}

Val::Val( Int32   val ) : op( new_number( val ) ) {}
Val::Val( Int64   val ) : op( new_number( val ) ) {}

Val::Val( Int32 num, Int32 den ) : op( new_number( num, den ) ) {}
Val::Val( Int64 num, Int64 den ) : op( new_number( num, den ) ) {}

Val::Val( Float32 val ) : op( new_number( double( val ) ) ) {}
Val::Val( Float64 val ) : op( new_number(         val   ) ) {}

Val::Val( const Val &ex ) : op( inc_ref( ex.op ) ) {}

Val &Val::operator=( const Val &ex ) {
    if ( op )
        dec_ref( op );
    op = inc_ref( ex.op );
    return *this;
}

bool Val::is_a_Number() const { return op->is_a_Number(); }

Val::operator double() const {
    double res;
    if ( not op->get_val( res ) )
        throw "not a number !";
    return res;
}

Val::operator long  () const {
    long res;
    if ( not op->get_val( res ) )
        throw "not a long number !";
    return res;
}

Val::~Val() { if ( op ) dec_ref( op ); }

Val Val::diff( const Val &variable ) const {
    ++ValItem::current_op_id;

    variable.op->op_id = ValItem::current_op_id;
    variable.op->op_mp = inc_ref( number_1 );

    // get diff
    op->get_diff();
    Val res( inc_ref( op->op_mp ? op->op_mp : number_0 ) );

    // dec_ref
    ++ValItem::current_op_id;
    op->dec_ref_op_mp_rec();

    return res;
}

BasicVec<Val> diff( const BasicVec<Val> &expressions, const Val &variable ) {
    ++ValItem::current_op_id;

    variable.op->op_id = ValItem::current_op_id;
    variable.op->op_mp = inc_ref( number_1 );

    // get diff
    for(int i=0;i<expressions.size();++i)
        expressions[ i ].op->get_diff();

    // store
    BasicVec<Val> res( SetSize(), expressions.size(), reinterpret_cast<const ValItem *>( 0 ) );
    for(int i=0;i<expressions.size();++i)
        res[ i ].op = inc_ref( expressions[ i ].op->op_mp ? expressions[ i ].op->op_mp : number_0 );

    // dec_ref
    ++ValItem::current_op_id;
    for(int i=0;i<expressions.size();++i)
        expressions[ i ].op->dec_ref_op_mp_rec();

    return res;
}

Val Val::subs( const Val &from, const Val &to ) const {
    return subs( BasicVec<Val>( from ), BasicVec<Val>( to ) );
}

Val Val::subs( const BasicVec<Val> &from, const BasicVec<Val> &to ) const {
    ++ValItem::current_op_id;

    for(int i=0;i<from.size();++i) {
        from[ i ].op->op_id = ValItem::current_op_id;
        from[ i ].op->op_mp = inc_ref( to[ i ].op );
    }

    // get subs
    op->get_subs();
    Val res( inc_ref( op->op_mp ? op->op_mp : op ) );

    // dec_ref
    ++ValItem::current_op_id;
    op->dec_ref_op_mp_rec();

    return res;
}

BasicVec<Val> subs( const BasicVec<Val> &expressions, const BasicVec<Val> &from, const BasicVec<Val> &to ) {
    ++ValItem::current_op_id;

    for(int i=0;i<from.size();++i) {
        from[ i ].op->op_id = ValItem::current_op_id;
        from[ i ].op->op_mp = inc_ref( to[ i ].op );
    }

    // get subs
    for(int i=0;i<expressions.size();++i)
        expressions[ i ].op->get_subs();

    // store
    BasicVec<Val> res( SetSize(), expressions.size(), reinterpret_cast<const ValItem *>( 0 ) );
    for(int i=0;i<expressions.size();++i)
        res[ i ].op = inc_ref( expressions[ i ].op->op_mp ? expressions[ i ].op->op_mp : expressions[ i ].op );

    // dec_ref
    ++ValItem::current_op_id;
    for(int i=0;i<expressions.size();++i)
        expressions[ i ].op->dec_ref_op_mp_rec();

    return res;
}


int Val::poly_deg( const BasicVec<Val> &variables ) const {
    ++ValItem::current_op_id;

    for(int i=0;i<variables.size();++i) {
        variables[ i ].op->op_id = ValItem::current_op_id;
        reinterpret_cast<int &>( variables[ i ].op->op_mp ) = 1;
    }

    op->poly_deg_rec();
    return reinterpret_cast<int &>( op->op_mp );
}

void Val::write_to_stream( Stream &os ) const {
    op->write_to_stream( os, 0 );
}

void Val::get_type_name( Stream &os ) const {
    op->get_type_name( os );
}

void Val::get_tiny_repr( Stream &os ) const {
    op->get_tiny_repr( os );
}

void Val::write_tex( Stream &os ) const {
    op->write_tex( os, 0 );
}

void Val::write_dot( Stream &os, bool want_parents ) const {
    ++ValItem::current_op_id;
    op->write_dot( os, want_parents );
}

void Val::display_tex( const String &base_filename, bool non_blocking ) const {
    File f( base_filename+".tex", "w" );

    f << "\\documentclass{article}\n";
    f << "\\usepackage[latin1]{inputenc}\n";
    f << "\\usepackage{amsmath}\n";
    f << "\\begin{document}\n";
    f << "\\pagestyle{empty}\n";
    f << "$$\n";
    write_tex( f );
    f << "$$\n";
    f << "\\end{document}\n";

    f.close();

    if ( exec_cmd( "latex --interaction=nonstopmode " + base_filename + ".tex > /dev/null 2> /dev/null" ) )
        return;
    if ( exec_cmd( "dvips -O0in,11in -E -o " + base_filename + ".eps " + base_filename + ".dvi > /dev/null 2> /dev/null" ) )
        return;
    if ( exec_cmd( "okular " + base_filename + ".eps" + String( non_blocking ? " &" : "" ) ) )
        return;
}

void Val::display_dot( const String &base_filename, bool want_parents ) const {
    File f( base_filename+".dot", "w" );
    f << "digraph my_graph {\n";
    write_dot( f, want_parents );
    f << "}\n";
    f.close();

    exec_cmd( "dot -Tpdf " + base_filename + ".dot > " + base_filename + ".pdf; okular " + base_filename + ".pdf" );
}

Val Val::operator+( const Val &ex ) const { return op->add( ex.op ); }
Val Val::operator-( const Val &ex ) const { return op->sub( ex.op ); }
Val Val::operator*( const Val &ex ) const { return op->mul( ex.op ); }
Val Val::operator/( const Val &ex ) const { return op->div( ex.op ); }

Val Val::operator-() const { return op->neg(); }

Val cos ( const Val &ex ) { return ex.op->cos(); }
Val sin ( const Val &ex ) { return ex.op->sin(); }
Val log ( const Val &ex ) { return ex.op->log(); }
Val exp ( const Val &ex ) { return ex.op->exp(); }
Val abs ( const Val &ex ) { return ex.op->abs(); }

Val sqrt( const Val &ex ) { return ex.op->pow( number_05 ); }
Val sqrt( int       a ) { return sqrt( Val( a ) ); }
// Val sqrt( unsigned  a ) { return sqrt( Val( a ) ); }

Val pow( const Val &a, const Val &b ) { return a.op->pow( b.op ); }

}

