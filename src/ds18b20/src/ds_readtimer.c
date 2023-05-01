#include "ds_readtimer.h"
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define GIGA 1000000000

int start_timer( ds_read_time_t *drt ){
        memset(drt, 0, sizeof( ds_read_time_t ));
        
        gettimeofday( &drt->start_time, NULL );

        return 0;
}
int end_timer(   ds_read_time_t *drt ){

        gettimeofday( &drt->end_time, NULL );
        return 0;
}

uint64_t        delta_time_us( ds_read_time_t *drt ){
        uint64_t time_us;
        struct timespec ts;

        ts = delta_time_ts( drt );
        time_us = ts.tv_sec * GIGA;
        time_us += ts.tv_nsec;
       
        return time_us;
}

struct timespec delta_time_ts( ds_read_time_t *drt ){
        struct timespec time_ts;

        time_ts.tv_sec = (drt->end_time.tv_sec) - (drt->start_time.tv_sec);
        time_ts.tv_nsec = (drt->end_time.tv_usec) - (drt->start_time.tv_usec);

        return time_ts;

}
