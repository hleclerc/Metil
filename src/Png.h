#ifndef PNG_H
#define PNG_H

#include "Ps.h"

BEG_METIL_NAMESPACE;

Ps<char> make_png( unsigned *img, int w, int h, const char *prelim = 0, ST prelim_size = 0 );

END_METIL_NAMESPACE;

#endif // PNG_H
