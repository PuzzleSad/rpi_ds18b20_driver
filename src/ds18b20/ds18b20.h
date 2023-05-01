#ifndef DS18B20_H
#define DS18B20_H

#include "../utils/str_utils.h"
#include <stdint.h>

#define VERIFY_ON_EVERY_READ    //Could be useful if a sensor dissapears
#define RESCAN_ON_EVERY_READ    //Looks for new ds sensors on every read

/*
        e
*/
#define DS_SEARCHPATH "/sys/bus/w1/devices/"

typedef struct ds18b20_t{
        // int family_code;
        uint64_t serial_number; //alias: ID
        char* path;
}ds18b20_t;


typedef struct ds_vtable_t{
        int random;
}ds_vtable_t;

//Due to the long term run nature of the driver, it might
//be prudent to setup a system that limits how many failures gets logged
typedef struct ds_errtable_t{

}ds_errtable_t;


typedef struct ds18b20_collection_t{
        ds_vtable_t vtable;

        int count;
        ds18b20_t  *sensors;
}ds18b20_collection_t;


int32_t ds_get_reading( ds18b20_collection_t* ds_collect, int sensor_num );
uint64_t ds_get_serial( const char* path );

int  init_ds18b20( ds18b20_t* ds, const char* path );
void fini_ds18b20( ds18b20_t* ds );

int write_vtable( ds_vtable_t* vtable );

int  init_ds18b20_collection( ds18b20_collection_t* ds_collect );
void fini_ds18b20_collection( ds18b20_collection_t* ds_collect );

// int init 


string_array_t* ds_possible_sensors(char* search_path); //dir in which it should search




#endif
