#ifndef PLOT_H
#define PLOT_H

#include "Pipe.h"

namespace Metil {

///
class Plot {
public:
    Plot();

    template<class TV>
    void plot( const TV &v ) {

    }
private:
    void *pipe;
};

template<class TV>
void plot( const TV &v ) {
    Plot p;
    p.plot( v );
}

} // namespace Metil

#endif // PLOT_H
