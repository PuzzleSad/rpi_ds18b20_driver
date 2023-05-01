#include "../ds18b20.h"
#include "../../utils/usefuldefines.h"
#include "../../utils/str_utils.h"
#include "../../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
//      AA is CRC
//      xx... is 48bit (6 byte) serial num
//      28 is family code
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

int  init_ds18b20_collection( ds18b20_collection_t* ds_collect );
void fini_ds18b20_collection( ds18b20_collection_t* ds_collect );
