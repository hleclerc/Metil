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

#include "LBasicVec.h"
#include "LVecItem.h"
#include "ValItemeration.h"
// #include "CodeWriter.h"
// #include "AutoPtr.h"

namespace Metil {

LVec::LVec() {
}

LVec::LVec( const LVec &l ) : items( l.items ) {
    for(int i=0;i<items.size();++i)
        inc_ref( items[ i ] );
}

LVec &LVec::operator=( const LVec &l ) {
    for(int i=0;i<l.items.size();++i)
        inc_ref( l.items[ i ] );
    for(int i=0;i<items.size();++i)
        dec_ref( items[ i ] );
    items = l.items;
    return *this;
}

LVec::~LVec() {
    for(int i=0;i<items.size();++i)
        dec_ref( items[ i ] );
}

LVec::LVec( const Range<Int32> &range ) : items( new LVecItemRange<Int32>( range ) ) {}

LVec::LVec( const Range<Int64> &range ) : items( new LVecItemRange<Int64>( range ) ) {}

LVec::LVec( const Range<Float32> &range ) : items( new LVecItemRange<Float32>( range ) ) {}

LVec::LVec( const Range<Float64> &range ) : items( new LVecItemRange<Float64>( range ) ) {}


LVec::S LVec::size() const {
    S res = 0;
    for(int i=0;i<items.size();++i)
        res += items[ i ]->size();
    return res;
}

Vec<const Type *,-1,1> LVec::types() const {
    BasicVec<const Type *,-1,1> res;
    for(int i=0;i<items.size();++i)
        res.push_back_unique( items[ i ]->type() );
    return res;
}

void LVec::write_to_stream( Stream &os ) const {
    LStream ls( &os );
    for(int i=0;i<items.size();++i)
        ls.append( items[ i ] );
}

//LVec LVec::binary_op( ValItemeration *op, const LVec &a, const LVec &b ) {
//    LVec res;
//    S o1 = 0, o2 = 0;
//    for( int i1=0,i2=0; i1 < a.items.size() and i2 < b.items.size(); ) {
//        S cs1 = a.items[ i1 ]->size() - o1;
//        S cs2 = b.items[ i2 ]->size() - o2;
//        if ( cs1 == cs2 ) {
//            res.items << new_LVecItemBinaryOp( op, a.items[ i1 ], b.items[ i2 ], o1, o2, cs1 );
//            o1 = 0;
//            o2 = 0;
//            ++i1;
//            ++i2;
//        } else if ( cs1 > cs2 ) {
//            res.items << new_LVecItemBinaryOp( op, a.items[ i1 ], b.items[ i2 ], o1, o2, cs2 );
//            o1 += cs2;
//            o2 = 0;
//            ++i2;
//        } else {
//            res.items << new_LVecItemBinaryOp( op, a.items[ i1 ], b.items[ i2 ], o1, o2, cs1 );
//            o1 = 0;
//            o2 += cs1;
//            ++i1;
//        }
//    }
//    return res;
//}
//
//LVec LVec::operator+( const LVec &b ) const { return binary_op( operation_plus, *this, b ); }
//
//LVec abs( const LVec &v ) {
//    LVec res;
//    for(int i=0;i<v.items.size();++i)
//        res.items << new_LVecItemUnaryOp( operation_abs, v.items[ i ] );
//    return res;
//}

//void LVec::get_values( const Type *type, void *data ) const {
//    if ( not items.size() )
//        return;
//
//    //
//    AutoPtr<CodeWriter> cw = new CodeWriterCpp( "cw.cpp" );
//    int data_id = cw->add_argument( ptr_on( type ) );
//    cw->write_header();
//
//    for(int i=0;i<items.size();++i) {
//        int loop_id, var_id;
//        items[ i ]->write_beg_for_loop( cw.ptr(), loop_id, var_id );
//        cw->write_assign_and_inc_ptr( data_id, var_id );
//        items[ i ]->write_end_for_loop( cw.ptr(), loop_id );
//    }
//    cw->write_footer();
//
//    void *arguments[] = { reinterpret_cast<void *>( &data ) };
//    cw->execute( arguments );
//}

}


