#ifndef DS_READTIMER_H
#define DS_READTIMER_H

#include <time.h>
#include <sys/time.h>
#include <stdint.h>

typedef struct ds_read_time_t{
        struct timeval start_time;
        struct timeval end_time;
}ds_read_time_t;

//ret 0 on success
int start_timer( ds_read_time_t *drt );
int end_timer(   ds_read_time_t *drt );

uint64_t        delta_time_us( ds_read_time_t *drt );
struct timespec delta_time_ts( ds_read_time_t *drt );

//4 x 10^9 Microseconds = 4,000 Seconds = 1.111 Hours

#endif
