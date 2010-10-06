#include "DefStr.h"
#include "Dout.h"
#include <sstream>

BEG_METIL_LEVEL1_NAMESPACE;

typedef DefStr::Str Str;

int DefStr::num_first_n_operator = 0;
BasicVec<DefStr::Operator> DefStr::operators;

static BasicVec<Str> tokenize( const Str &str, const Str &sep ) {
    BasicVec<Str> res;
    Str::size_type old_n = 0;
    while ( true ) {
        Str::size_type n = str.find( sep, old_n );
        res.push_back( str.substr( old_n, n - old_n ) );
        if ( n == Str::npos )
            return res;
        old_n = n + sep.size();
    }
}

DefStr::DefStr( const Str &file, int line, const Str &str ) {
    init( file, line, str );
}

DefStr::DefStr( const DefStr &def_str ) {
    init( def_str.file, def_str.line, def_str.orig );
}

void DefStr::init( const Str &file, int line, const Str &orig ) {
    this->file = file;
    this->line = line;
    this->orig = orig;

    // DOUT( str );
    update_operators();

    // tokenize
    BasicVec<Str> l = tokenize( orig.substr( 10 ), "__" );
    if ( l.size() == 0 )
        return;

    // first pass -> creation of items
    name = l[ 0 ];
    Item *prev = items.push_back();
    byop.resize( operators.size(), (Item *)0 );
    for( int i = 1; i < l.size(); ++i ) {
        Item *item = items.push_back( l[ i ] );
        item->prev = prev;
        if ( prev )
            prev->next = item;
        prev = item;
        //
        for( int o = 0; o < operators.size(); ++o ) {
            if ( operators[ o ].name == item->name ) {
                item->sibling = byop[ o ];
                byop[ o ] = item;
                break;
            }
        }
    }

    // parenthesis
    for( Item *item = byop[ num_operator("beg") ]; item; item = item->sibling ) {
        TODO;
    }

    // make children
    for( int n = 0; n < num_first_n_operator; ++n ) {
        for( Item *o = byop[ n ]; o; o = o->sibling ) {
            if ( operators[ n ].type == Operator::lr ) {
                ASSERT( o->prev, "operator %s needs a left argument" , operators[ n ].name );
                ASSERT( o->next, "operator %s needs a right argument", operators[ n ].name );

                // prev
                if ( o->prev->parent ) {
                    o->parent = o->prev->parent;
                    if ( o->prev->parent->children[ 0 ] == o->prev )
                        o->prev->parent->children[ 0 ] = o;
                    else
                        o->prev->parent->children[ 1 ] = o;
                }

                if ( o->prev->prev )
                    o->prev->prev->next = o;

                o->children[ 0 ] = o->prev;
                o->children[ 0 ]->parent = o;
                o->prev = o->prev->prev;

                o->children[ 0 ]->next = NULL;
                o->children[ 0 ]->prev = NULL;

                // next
                if ( o->next->next )
                    o->next->next->prev = o;

                o->children[ 1 ] = o->next;
                o->children[ 1 ]->parent = o;
                o->next = o->next->next;

                o->children[ 1 ]->prev = NULL;
                o->children[ 1 ]->next = NULL;
            } else if ( operators[ n ].type == Operator::r ) {
                ASSERT( o->next, "operator %s needs a right argument", operators[ n ].name );

                if ( o->next->next )
                    o->next->next->prev = o;

                o->children[0] = o->next;
                o->children[0]->parent = o;
                o->next = o->next->next;

                o->children[0]->prev = NULL;
                o->children[0]->next = NULL;
            } else {
                ERROR( "Type %i", operators[ n ].type );
            }
        }
    }
}


void DefStr::update_operators() {
    if ( operators.size() == 0 ) {
        operators.push_back( "is"  , Operator::lr );
        operators.push_back( "isa" , Operator::lr );
        operators.push_back( "has" , Operator::lr );
        operators.push_back( "or"  , Operator::lr );
        operators.push_back( "and" , Operator::lr );
        operators.push_back( "when", Operator::r  );
        operators.push_back( "pert", Operator::r  );

        operators.push_back( "beg" , Operator::n  );
        operators.push_back( "end" , Operator::n  );

        num_first_n_operator = num_operator( "beg" );
    }
}

int DefStr::num_operator( Str name ) {
    for( int o = 0; o < operators.size(); ++o )
        if ( operators[ o ].name == name )
            return o;
    return -1;
}

int DefStr::num_child( Str name ) const {
    if ( name == "a" ) return 0;
    if ( name == "b" ) return 1;
    if ( name == "c" ) return 2;
    return -1;
}

Str DefStr::item_to_cond_str_rec( Item *item, Str &type, BasicVec<Str> &init, Str arg ) const {
    if ( item->name == "or" ) {
        type += "MethodCond_or<";
        item_to_cond_str_rec( item->children[ 0 ], type, init, arg + ".cond_0" );
        type += ",";
        item_to_cond_str_rec( item->children[ 1 ], type, init, arg + ".cond_1" );
        type += " >";
    }
    if ( item->name == "and" ) {
        type += "MethodCond_and<";
        item_to_cond_str_rec( item->children[ 0 ], type, init, arg + ".cond_0" );
        type += ",";
        item_to_cond_str_rec( item->children[ 1 ], type, init, arg + ".cond_1" );
        type += " >";
    }
    if ( item->name == "isa" ) {
        std::ostringstream ss;
        ss << "MethodCond_" << num_child( item->children[ 0 ]->name ) << "_isa<TypeConstructor_" << item->children[ 1 ]->name << ">";
        type += ss.str();
    }
    if ( item->name == "is" ) {
        std::ostringstream ss;
        ss << "MethodCond_" << num_child( item->children[ 0 ]->name ) << "_is";
        init << arg + ".type = \"" + item->children[ 1 ]->name + "\";";
        type += ss.str();
    }
    if ( item->name == "has" ) {
        std::ostringstream ss;
        ss << "TypeConstructor::C" << num_child( item->children[ 0 ]->name ) << "_has_" << item->children[ 1 ]->name;
        type += ss.str();
    }
    return item->name;
}

BasicVec<Str> DefStr::type_constructors() const {
    BasicVec<Str> res;
    for( Item *item = byop[ num_operator( "isa" ) ]; item; item = item->sibling )
        res.push_back_unique( item->children[ 1 ]->name );
    return res;
}

void DefStr::cond( Str &type, BasicVec<Str> &init ) const {
    // checks
    Item *when = byop[ num_operator( "when" ) ];

    if ( when == 0 ) {
        type += "MethodCond_True";
        return;
    }
    ASSERT( when, "no declared cond" );
    ASSERT( when->sibling == 0, "two when in the same definition is weird" );
    ASSERT( when->children[ 0 ], "a when without child is weird" );
    ASSERT( when->children[ 0 ]->next == 0, "2 expression above a when is weird" );

    // string
    item_to_cond_str_rec( when->children[ 0 ], type, init );
}

FP64 DefStr::pert() const {
    Item *pert = byop[ num_operator( "pert" ) ];
    if ( pert and pert->children[ 0 ] )
        return atof( pert->children[ 0 ]->name.c_str() );
    return 0;
}

END_METIL_LEVEL1_NAMESPACE;
