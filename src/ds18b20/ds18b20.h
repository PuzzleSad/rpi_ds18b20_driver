#ifndef DS18B20_H
#define DS18B20_H

#include "../utils/str_utils.h"

/*
        
*/
#define DS_SEARCHPATH "/sys/bus/w1/devices/"

typedef struct ds18b20_t{
        char* UUID;


}ds18b20_t;


typedef struct ds_vtable_t{
        
}ds_vtable_t;


typedef struct ds18b20_collection_t{
        ds_vtable_t vtable;

        int count;
        ds18b20_t  *sensors;
}ds18b20_mgmt_t;

string_array_t* ds_possible_sensors(char* search_path); //dir in which it should search




#endif
