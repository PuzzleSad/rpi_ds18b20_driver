#include "ds_utils.h"

#include "../../utils/usefuldefines.h"
#include "../../utils/str_utils.h"
#include "../../utils/utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



char* ds_splice_path(const char* ds_path, const char* file){

        size_t path_len = 0;
        size_t path_slash_check = 0;
        // size_t append_len = 0;

        path_len += strlen(ds_path);
        path_slash_check = path_len;
        path_len += strlen(file);

        // char read_path[path_len +1];
        char *read_path = (char*)calloc( path_len +1, sizeof(char) );


        strcpy( read_path, ds_path );

        if( read_path[path_slash_check-1] == '/' ){
                read_path[path_slash_check-1] = '\0';
        }

        if( file[0] != '/' ){
                read_path[path_slash_check] = '/';
        }

        strcat( read_path, file );


        return read_path;
}
