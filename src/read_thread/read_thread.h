#ifndef READ_THREAD_H
#define READ_THREAD_H

#include "../ds18b20/ds18b20.h"

typedef struct ds_reader_priv_t ds_reader_priv_t;

#include <pthread.h>

typedef struct ds_reader_t{
        ds18b20_collection_t *dsct;

        pthread_cond_t completion_cond;
        pthread_mutex_t completion_mtx;
        ds_reader_priv_t *private;
}ds_reader_t;

int ds_reader_init( ds_reader_t* dr );
int ds_reader_fini( ds_reader_t* dr );

/* These functions apply to if its preffered to keep the thread alive */
int ds_reader_set_keepalive( ds_reader_t* dr );
int ds_reader_is_keepalive( ds_reader_t* dr );
int ds_reader_setup_thread( ds_reader_t* dr );
int ds_reader_set_collection( ds_reader_t* dr, ds18b20_collection_t* dsct );




#endif
