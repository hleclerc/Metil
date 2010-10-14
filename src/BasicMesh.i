%{
    #include "BasicMesh.h"
%}

namespace Metil {
    class BasicMesh {
    public:
        void add_node( float x, float y, float z );
        // void add_elem( const ElemType *elem_type, T x, T y, T z );
        // ElemGroup *find_group( const ElemType *elem_type );
    };
    %extend BasicMesh {
        void add_triangle( int x, int y, int z ) { self->add_elem( Metil::elem_type_Triangle, x, y, z ); }
    }
}
