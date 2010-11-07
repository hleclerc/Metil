#include "CompilationTree.h"
#include "System.h"

BEG_METIL_LEVEL1_NAMESPACE;

static SI64 cur_op_id = 0;

CompilationTree::CompilationTree( const String &dst ) : dst( dst ), op_id( 0 ) {
}

void CompilationTree::add_child( const Ptr<CompilationTree> &ch ) {
    children << ch;
    ch->parents.push_back_unique( this );
}

static void get_leaves( BasicVec<CompilationTree *> &leaves, CompilationTree *c ) {
    if ( c->op_id == cur_op_id )
        return;
    c->op_id = cur_op_id;

    if ( c->children.size() == 0 )
        leaves << c;
    else
        for( int i = 0; i < c->children.size(); ++i )
            get_leaves( leaves, c->children[ i ].ptr() );
}

static bool all_child_done( CompilationTree *c ) {
    for( int i = 0; i < c->children.size(); ++i )
        if ( c->children[ i ]->op_id != cur_op_id )
            return false;
    return true;
}

int CompilationTree::exec_node( String *out ) {
    if ( not cmd )
        return 0;

    // dates
    bool need_rebuild = false;
    SI64 date_dst = last_modification_time_or_zero_of_file_named( dst );
    for( int i = 0; i < children.size(); ++i ) {
        SI64 date_src = last_modification_time_or_zero_of_file_named( children[ i ]->dst );
        need_rebuild |= date_src > date_dst;
    }
    if ( not need_rebuild )
        return false;

    // exec
    if ( out )
        *out << cmd << String::endl;
    return exec_cmd( cmd, false );
}

int CompilationTree::exec( String *out ) {
    BasicVec<CompilationTree *> leaves;
    ++cur_op_id;
    get_leaves( leaves, this );

    //
    ++cur_op_id;
    while ( leaves.size() ) {
        CompilationTree *c = leaves.pop_back();
        c->op_id = cur_op_id;
        if ( int res = c->exec_node( out ) )
            return res;

        //
        for( int i = 0; i < c->parents.size(); ++i )
            if ( all_child_done( c->parents[ i ] ) )
                leaves << c->parents[ i ];
    }

    return 0;
}

END_METIL_LEVEL1_NAMESPACE;

