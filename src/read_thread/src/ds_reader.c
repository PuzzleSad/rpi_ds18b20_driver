#include "../../utils/str_utils.h"
#include "../../utils/usefuldefines.h"
#include "../../ds18b20/ds18b20.h"
#include "../read_thread.h"
#include "ds_reader_priv.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

/*
        Notes: 
        pthread init functions ret 0 on success
        pthread destroy functions ret 0 on success

*/


static int init_locals( ds_reader_t* dr );
static int init_privs( ds_reader_priv_t* pdr );

static int fini_locals( ds_reader_t* dr );
static int fini_privs( ds_reader_priv_t* pdr );




int ds_reader_init( ds_reader_t* dr ){
        if(dr == NULL){
                printerr_loc("Error, arg equals NULL\n");
        }

        memset( dr, 0, sizeof(ds_reader_t) );

        dr->private = (ds_reader_priv_t*)calloc( 1, sizeof(ds_reader_priv_t) );

        init_locals( dr );
        init_privs( dr->private );


        return 1;
}

int ds_reader_fini( ds_reader_t* dr ){
        if( !fini_locals( dr )          ) goto EXIT_FAIL;
        if( !fini_privs( dr->private ) ) goto EXIT_FAIL;
        free( dr->private );


        return 1;

        EXIT_FAIL: ;
        printerr_loc("Failure to fini");
        return 0;
}

int ds_reader_set_keepalive( ds_reader_t* dr ){
        ds_reader_priv_t* ds_priv = dr->private;
        ds_priv->keepalive = 1;

        //TODO either refactor to void or implement debug check
        return 1;
}
int ds_reader_is_keepalive( ds_reader_t* dr ){
        ds_reader_priv_t* ds_priv = dr->private;
        return ds_priv->keepalive;
}

int ds_reader_set_collection( ds_reader_t* dr, ds18b20_collection_t* dsct ){
        dr->dsct = dsct;

        // TODO sanity check or refactor
        return 1;
}

static int init_locals( ds_reader_t* dr ){

        if( pthread_cond_init ( &dr->completion_cond, NULL ) ) goto EXIT_FAIL;
        if( pthread_mutex_init( &dr->completion_mtx , NULL ) ) goto EXIT_FAIL;


        return 1;


        //Apologies for the goto, didn't feel like writing an error message for each init
        //TODO possible future analysis for nicer debug

        EXIT_FAIL: ;
        printerr_loc("Failure to init ds_reader_t");
        return 0;

}

static int init_privs( ds_reader_priv_t* pdr ){
        
        
        if( pthread_mutex_init( &pdr->mtx, NULL ) ) goto EXIT_FAIL;

        return 1;

        EXIT_FAIL: ;
        printerr_loc("Failure to init ds_reader_priv_t");
        return 0;
}

static int fini_locals( ds_reader_t* dr ){

        if( pthread_cond_destroy( &dr->completion_cond ) ) goto EXIT_FAIL;
        if( pthread_mutex_destroy( &dr->completion_mtx ) ) goto EXIT_FAIL;

        return 1;

        EXIT_FAIL: ;
        printerr_loc("Failure to fini ds_reader_priv_t");
        return 0;
}

static int fini_privs( ds_reader_priv_t* pdr ){

        if( pthread_mutex_destroy( &pdr->mtx ) ) goto EXIT_FAIL;


        return 1;

        EXIT_FAIL: ;
        printerr_loc("Failure to fni ds_reader_priv_t");
        return 0;
}
