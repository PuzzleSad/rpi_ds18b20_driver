#include "../ds18b20.h"

#include "../../utils/str_utils.h"
#include "../../utils/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

static string_array_t* search_sensors(char* search_path);

string_array_t* ds_possible_sensors(char* search_path){
        if( search_path == NULL ){
               return search_sensors( DS_SEARCHPATH );
        }else{
                return search_sensors( search_path );
        }



        
}


static string_array_t* search_sensors(char* search_path){
        if( !step_validatepath(search_path) ){
                return NULL;
        }

        string_array_t* sa;
        sa = (string_array_t*)calloc( 1, sizeof( string_array_t ) );

        DIR* dir;
        struct dirent* entry;
        dir = opendir( search_path );
        if( dir == NULL ){
                fprintf(stderr, "DIR opendir failed, in search_sensors\n");
                return NULL;
        }

        while( (entry = readdir(dir)) != NULL ){
                if( strstr( entry->d_name, "28-" ) ){
                        su_stringarr_insert( sa, entry->d_name );
                }
        }



        closedir( dir );
        return sa;
}
