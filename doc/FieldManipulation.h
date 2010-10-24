/*! \page FieldManipulation Field and geometry manipulations

    In Metil, as all the "mathematical" objects (Val, Vec, Mat, ...) can become symbolic, they can depend on symbolic variables like axes (X, Y, T, ...), and have domain of definition.

    For example:
    @code
// a will be a field that depend on X. It is defined on an infinite domain
Val a = 1 + Axes::X;

// to integrate a, it is possible to define a domain
Geo g = NEW( UnitSquare, Axes::space( 2 ) );
PRINT( integration( a, g ) );

// b will be a field defined on a 2 dimensionnal mesh
Geo m = NEW( Mesh, "toto.unv" );
Vec nodal_values( ... );
Val b = m.new_Field( nodal_values );

// meaning that b has a restrictive domain of definition
PRINT( integration( b ) );
    @endcode

@section FieldAxes Axes

    @p Axes is a namespace. Thus, it can be extended... but primarily, axes are only simple symbols.
    
    
@section FieldDomain Fields defined using multiple and "incompatible" domains

It is possible to add, multiply, ... fields defined on different domains.

In this case,
    - the domain of definition will be the intersection of the one from the children fields.
    - it is a "composite" field, meaning that it cannot be reassigned to a field of a simple type (e.g. a field on a mesh). If you want to project a field, you can use a projector function (which prominently needs a norm).

One have to notive that manipulation of fields defined on high order elements is not trivial, because it is necessary to project the interpolation variables if the elements are not compatibles. It is simple in the case where at most one element has a non linear interpolation.


@section FieldDisplay Displaying fields

    The @p display method uses OpenGL and home made tools (because the fields are not necessarily on simple meshes, without spatio-temporal compression...). But it is possible to save them to files that software like Paraview, ... can read.
    
    For more information, see @subpage Visualisation

*/
