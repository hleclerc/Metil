/*! @page ProblemDefinition Problem definition

    A data setting is a C++ file which refers to metil's file thanks to #include statements.

    Compilation is assisted through a small script named @p metil_comp which basically detects dependencies, compiles associated files (if needed), links the whole thing and execute the program (if asked for, under the supervision of a debugger like gdb or valgrind). This organization implies that if the C++ data setting is modified, recompilation is required, though since a priori few files need recompiling, time is not an issue. One interest of this data setting is to naturly enables to run complex simulations (including loops over different data setting, use of if statements), basically it avoids the definition of a script language which is now a feature classically added on top of FE software (and thus not perfectly embedded).

    This is a short example of a mechanical problem definition:
    
@code
#include <Elasticity.h>
using namespace Metil;
int main() {
    Geo g1( "conrod.unv" );
    Problem p;
    p.add_( g1, Elasticity( 210e9, 0.33 ) );
    p.add_CL( g1["lower part"][Axes::X] == 0 );
    p.solve();
    ... À compléter avec la C^5
}
@endcode

/*
