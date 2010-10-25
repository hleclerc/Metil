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

//#include "LVecItem.h"
//#include "Type.h"
//#include "ValItemeration.h"

namespace Metil {

// -------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------
///
//template<int nb_ch>
//class LVecItemByItemOp : public LVecItem {
//public:
//    // unary
//    LVecItemByItemOp( const ValItemeration *operation, const LVecItem *c0, S o0, S s ) : op( operation ) {
//        ch[ 0 ] = c0;
//        of[ 0 ] = o0;
//        _type = type_promote( op, c0->type() );
//        _size = s;
//        c0->add_parent( this );
//    }
//    // binary
//    LVecItemByItemOp( const ValItemeration *operation, const LVecItem *c0, const LVecItem *c1, S o0, S o1, S size ) : op( operation ) {
//        ch[ 0 ] = c0; ch[ 1 ] = c1;
//        of[ 0 ] = o0; of[ 1 ] = o1;
//        _type = type_promote( op, c0->type(), c1->type() );
//        _size = size;
//        c0->add_parent( this );
//        c1->add_parent( this );
//    }
//    ~LVecItemByItemOp() {
//        for(int i=0;i<nb_ch;++i)
//            ch[ i ]->rem_parent( this );
//    }
//    virtual S size() const { return _size; }
//    virtual const Type *type() const { return _type; }
//
//    virtual void exec_node() const {}
//    virtual bool done() const { return false; }
//    virtual void get_leaves( BasicVec<const LazyObject *> &leaves ) const {}
//
//
//    virtual void write_beg_for_loop( CodeWriter *cw, int &loop_id, int &var_id ) const {
//        throw "TODO";
//    }
//
//    const ValItemeration *op;
//    const Type *_type;
//    const LVecItem *ch[ nb_ch ];
//    S _size;
//    S of[ nb_ch ];
//};
//
//LVecItem *new_LVecItemBinaryOp( const ValItemeration *op, const LVecItem *a, const LVecItem *b, LVecItem::S o1, LVecItem::S o2, LVecItem::S size ) {
//    return new LVecItemByItemOp<2>( op, a, b, o1, o2, size );
//}
//
//LVecItem *new_LVecItemUnaryOp( const ValItemeration *op, const LVecItem *a ) {
//    return new LVecItemByItemOp<1>( op, a, 0, a->size() );
//}

} // namespace Metil
