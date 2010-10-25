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

#ifndef METIL_MESH_H
#define METIL_MESH_H

#include "GeometricSupport.h"
#include "BasicVec.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file Mesh.cpp
#endif

namespace Metil {

/**
*/
class Mesh {
public:
    ////
    class SubElemList {
    public:
        const ElementType *elem_type;
        LMatItem *con;
    };

    Mesh( const CString &filename ) {
        read_msh2( filename );
    }
    void read_msh2( const CString &filename ) {

    }

    LMat pos;
    LMat con;
};


//class Mesh;
//
//struct Triangle {
//    static const char *name() { return "Triangle"; }
//    static const int nb_nodes = 3;
//};
//
//template<class T0,class TE,class T1,class T2>
//void make_rect( Mesh &m, TE, const T0 &b, const T1 &e, const T2 &d );
//
///**
//
//*/
//class Mesh : public GeometricSupport {
//public:
//    struct ElemGroup {
//        template<class TE>
//        ElemGroup( const TE &te, const String &group ) : group( TE::name() ), connectivity( SetSize(), TE::nb_nodes ) {}
//        void write_to_stream( Stream &stream ) const {
//            stream << "group=" << group << Stream::endl;
//            for(int i=0;i<connectivity.size();++i)
//                stream << " con=" << connectivity[ i ] << Stream::endl;
//        }
//        int nb_elements() const { return connectivity.size() ? connectivity[ 0 ].size() : 0; }
//        String group;
//        BasicVec<Vec<int> > connectivity;
//    };
//    struct MakeRect {};
//
//    Mesh() {}
//
//    int dim() const { return pos.size(); }
//    int nb_nodes() const { return pos.size() ? pos[ 0 ].size() : 0; }
//
//    template<class TE,class T0,class T1,class T2>
//    Mesh( MakeRect, const TE &te, const T0 &b, const T1 &e, const T2 &i ) {
//        make_rect( *this, te, b, e, i );
//    }
//
//    template<class TE>
//    int find_elem_group( const TE &te, const String &group = "toto" ) {
//        for(int i=0;i<elem_group.size();++i)
//            if ( elem_group[ i ].group == TE::name() )
//                return i;
//        int res = elem_group.size();
//        elem_group.push_back( te, group );
//        return res;
//    }
//
//    template<class TE>
//    void add_elem( const TE &e, const BasicVec<int,TE::nb_nodes> &con ) {
//        int grp = find_elem_group( e );
//        for(int j=0;j<con.size();++j)
//            elem_group[ grp ].connectivity[ j ] << con[ j ];
//    }
//
//    template<class TP>
//    void add_node( const TP &p ) {
//        if ( not pos.size() )
//            pos.resize( p.size() );
//        for(int i=0;i<p.size();++i)
//            pos[ i ] << p[ i ];
//    }
//
//    void write_to_stream( Stream &stream ) const {
//        for(int i=0;i<pos.size();++i)
//            stream << pos[ i ] << Stream::endl;
//        stream << "elem_group=" << elem_group;
//    }
//
//    BasicVec<Vec<double> > pos;
//    BasicVec<ElemGroup> elem_group;
//};
//
//template<class T0,class T1,class T2>
//void make_rect( Mesh &m, const Triangle &te, const T0 &b, const T1 &e, const T2 &d ) {
//    BasicVec<double,2> beg( b );
//    BasicVec<double,2> end( e );
//    BasicVec<int,2>    div( d );
//    for(int y=0;y<div[1];++y)
//        for(int x=0;x<div[0];++x)
//            m.add_node( BasicVec<double,2>( beg[0] + ( end[0] - beg[0] ) * x / ( div[0] - 1 ), beg[1] + ( end[1] - beg[1] ) * y / ( div[1] - 1 ) ) );
//    for(int y=0;y<div[1]-1;++y) {
//        for(int x=0;x<div[0]-1;++x) {
//            m.add_elem( te, BasicVec<int,3>(
//                ( y + 0 ) * div[ 0 ] + ( x + 0 ),
//                ( y + 0 ) * div[ 0 ] + ( x + 1 ),
//                ( y + 1 ) * div[ 0 ] + ( x + 0 )
//            ) );
//            m.add_elem( te, BasicVec<int,3>(
//                ( y + 0 ) * div[ 0 ] + ( x + 1 ),
//                ( y + 1 ) * div[ 0 ] + ( x + 1 ),
//                ( y + 1 ) * div[ 0 ] + ( x + 0 )
//            ) );
//        }
//    }
//}

}

#endif // METIL_MESH_H
