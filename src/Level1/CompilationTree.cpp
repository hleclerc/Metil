#include "CompilationTree.h"
#include "System.h"
#include "Thread.h"
#include "WaitCondition.h"

BEG_METIL_LEVEL1_NAMESPACE;

static SI64 cur_op_id = 0;

CompilationTree::CompilationTree( const String &dst ) : dst( dst ), op_id( 0 ) {
}

void CompilationTree::add_child( const Ptr<CompilationTree> &ch ) {
    children << ch;
    ch->parents.push_back_unique( this );
}

static void save_Makefile_rec( CompilationTree *c, String &os, const BasicVec<String> &dep ) {
    if ( c->op_id == cur_op_id )
        return;
    c->op_id = cur_op_id;

    if ( c->cmd ) {
        os << c->dst << ':';
        for( int i = 0; i < dep.size(); ++i )
            os << ' ' << dep[ i ];
        for( int i = 0; i < c->children.size(); ++i )
            os << ' ' << c->children[ i ]->dst;
        os << '\n';
        os << '\t' << c->cmd << "\n\n";
    }

    // rec
    for( int i = 0; i < c->children.size(); ++i )
        save_Makefile_rec( c->children[ i ].ptr(), os, dep );
}

void CompilationTree::save_Makefile( String &os, const BasicVec<String> &dep ) {
    ++cur_op_id;
    save_Makefile_rec( this, os, dep );
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
    if ( not need_rebuild ) {
        File cmd_file( dst + ".cmd", "r" );
        const char *cmd_data = cmd_file.c_str();
        if ( cmd_data == 0 or cmd != cmd_data )
            need_rebuild = true;
    }
    if ( not need_rebuild )
        return false;

    //
    File cmd_file( dst + ".cmd", "w" );
    cmd_file << cmd;

    // exec
    if ( out )
        *out << cmd << "\n";
    return exec_cmd( cmd, false );
}

struct Leaves {
    Leaves( int nb_threads, String *out ) : out( out ), return_code( 0 ), nb_threads( nb_threads ), nb_waiting_threads( 0 ) {}

    void exec() {
        while ( return_code == 0 ) {
            // no leaf to execute ?
            mutex.lock();
            if ( not data.size() ) {
                if ( ++nb_waiting_threads == nb_threads ) {
                    wait_cond.wake_all();
                    mutex.free();
                    break;
                }
                wait_cond.wait( mutex );
                if ( nb_waiting_threads == nb_threads ) {
                    mutex.free();
                    break;
                }
                --nb_waiting_threads;
                mutex.free();
                continue;
            }

            CompilationTree *c = data.pop_back();
            mutex.free();

            // exec
            if ( int res = c->exec_node( out ) ) {
                return_code = res;
                mutex.lock();
                wait_cond.wake_all();
                mutex.free();
                break;
            }

            // new node to execute ?
            mutex.lock();
            c->op_id = cur_op_id;
            for( int i = 0; i < c->parents.size(); ++i )
                if ( all_child_done( c->parents[ i ] ) )
                    data << c->parents[ i ];
            if ( data.size() )
                wait_cond.wake_all();
            mutex.free();
        }
    }

    Mutex mutex;
    WaitCondition wait_cond;
    String *out;
    BasicVec<CompilationTree *> data;
    int return_code, nb_threads, nb_waiting_threads;
};

struct CompilationTreeThread : public Thread {
    CompilationTreeThread( Leaves *l ) : l( l ) {}
    virtual void run() { l->exec(); }
    Leaves *l;
};

int CompilationTree::exec( int nb_threads, String *out ) {
    Leaves leaves( nb_threads, out );
    ++cur_op_id;
    get_leaves( leaves.data, this );

    //
    ++cur_op_id;
    BasicVec<CompilationTreeThread> threads( Size(), nb_threads, &leaves );
    for( int i = 0; i < nb_threads; ++i ) threads[ i ].exec();
    for( int i = 0; i < nb_threads; ++i ) threads[ i ].wait();
    return leaves.return_code;
}

END_METIL_LEVEL1_NAMESPACE;

