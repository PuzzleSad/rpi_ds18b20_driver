#include "../ds18b20.h"
#include "../../utils/usefuldefines.h"
#include "../../utils/str_utils.h"
#include "../../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

//-------------MACROS---------------
#ifdef VERIFY_ON_EVERY_READ

#define PATH_VERIFY(path)\
do{\
        if( !step_validatepath(path) ){\
                printerr_loc("ds18 path not valid\n");\
                return 0;\
        }\
}while(0);

#else

#define PATH_VERIFY(path) do{}while(0);

#endif
//---------------------------------
//------MAGIC NUMBERS--------------
#define DS18B20_SERIAL_MASK 0x00ffffffffffff00
//                            AAxxxxxxxxxxxx28
//      AA is a CRC
//      xx... is a 48bit (6 byte) serial num
//      28 is a family code
//---------------------------------






int32_t ds_get_reading( ds18b20_collection_t* ds_collect, int sensor_num ){

        


        return 0;

}

uint64_t ds_get_serial( const char* path ){

        uint64_t serial;
        char append[4] = "/id\0";
        size_t path_len = 0;
        size_t path_slash_check = 0;

        path_len += strlen(path);
        path_slash_check = path_len;
        path_len += strlen(append);

        char read_path[path_len +1];
        memset( read_path, 0, path_len +1);

        strcpy( read_path, path );

        if( read_path[path_slash_check-1] == '/' ){
                read_path[path_slash_check-1] = '\0';
        }

        strcat( read_path, append );

        PATH_VERIFY(read_path); //ret 0 if fail


        FILE *fp = fopen( read_path, "r" );
        if( fp == NULL ){
                printerr_loc("File open failed\n");
                return 0;
        }

        uint64_t result;
        fread( &result, sizeof(uint64_t), 1, fp );
        fclose(fp);

        result = result & DS18B20_SERIAL_MASK;  //Mask out CRC and family code
        result = result >> 8;   //Shift into the now empty family_code byte

        /* TODO insert a CRC check here */

        return result;
}

int ds_collection_append( ds18b20_collection_t* ds_collect, ds18b20_t* ds ){
        
        //Realloc, +1 extra array slot
        size_t mem_size = 0;
        ds_collect->count++;
        mem_size = sizeof( ds18b20_t ) * ds_collect->count;
        ds_collect->sensors = (ds18b20_t*)realloc( ds_collect->sensors, mem_size ); 

        memcpy( 
                &ds_collect->sensors[ds_collect->count-1], /*dst*/
                ds,                                        /*src*/
                sizeof(ds18b20_t)
        );

        /*TODO possible error checks*/
        return 1;
}

int  init_ds18b20( ds18b20_t* ds, const char* path ){
        if( path == NULL ){
                printerr_loc("input arg NULL\n");
                return 0;
        }

        if( !step_validatepath(path) ){
                printerr_loc("ds18 path not valid\n");
                return 0;
        }

        ds->serial_number = ds_get_serial(path);

        size_t str_len = strlen(path);
        ds->path = (char*)calloc( (str_len + 1), sizeof(char) );
        memcpy( ds->path, path, str_len );

        return 1;
        
}
void fini_ds18b20( ds18b20_t* ds ){
        if( ds == NULL ){
                printerr_loc("input arg NULL\n");
                return;
        }

        free(ds->path);
}

int write_vtable( ds_vtable_t* vtable ){
        memset( vtable, 0, sizeof(ds_vtable_t) );
        return 1;
}

int  init_ds18b20_collection( ds18b20_collection_t* ds_collect ){
        memset(ds_collect, 0, sizeof( ds18b20_collection_t ) );
        return 1;
}
void fini_ds18b20_collection( ds18b20_collection_t* ds_collect ){

        if( ds_collect->vtable != NULL ){
                free( ds_collect->vtable );
        }

        for( int i = 0; i < ds_collect->count; i++){
                free( &ds_collect->sensors[i] );
        }
}

void ds_collection_printall( ds18b20_collection_t* ds_collect){
        if( ds_collect == NULL ){
                printerr_loc("Input arg null");
                return;
        }

        

        for( int i = 0; i < ds_collect->count; i++){
                printf("Path:   %s\n", ds_collect->sensors[i].path);
                printf("Serial: %"PRIx64"\n", ds_collect->sensors[i].serial_number);
        }

}
