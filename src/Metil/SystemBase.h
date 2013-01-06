#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include "TypeConfig.h"

BEG_METIL_NAMESPACE;

// time
double time_of_day_in_sec();

// hardware info
ST get_total_system_memory();
int get_nb_cpu_cores();

END_METIL_NAMESPACE;

#endif // SYSTEMBASE_H
