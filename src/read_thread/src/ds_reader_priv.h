#ifndef DS_READER_PRIV_H
#define DS_READER_PRIV_H

#include <pthread.h>

struct ds_reader_priv_t{
        int keepalive;
        pthread_t thread;
        pthread_mutex_t mtx;
};





#endif
