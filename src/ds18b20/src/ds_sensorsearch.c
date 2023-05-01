#include "../ds18b20.h"

#include "../../utils/str_utils.h"
#include "../../utils/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static string_array_t* search_sensors(char* search_path);

string_array_t* ds_possible_sensors(char* search_path){
        if( search_path == NULL ){
               return search_sensors( DS_SEARCHPATH );
        }else{
                return search_sensors( search_path );
        }



        
}


static string_array_t* search_sensors(char* search_path){

        return NULL;
}
