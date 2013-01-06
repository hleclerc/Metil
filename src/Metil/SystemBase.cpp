#include "SystemBase.h"
#include <sys/time.h>   // time_of_day_in_sec()
#include <unistd.h>     // getcwd

BEG_METIL_NAMESPACE;

double time_of_day_in_sec() {
    struct timeval st;
    struct timezone toto;
    gettimeofday( &st, &toto );
    return st.tv_sec + st.tv_usec / 1e6;
}

ST get_total_system_memory() {
    ST pages = sysconf( _SC_PHYS_PAGES );
    ST page_size = sysconf( _SC_PAGE_SIZE );
    return pages * page_size;
}

int get_nb_cpu_cores() {
    return sysconf( _SC_NPROCESSORS_ONLN );
}

END_METIL_NAMESPACE;
