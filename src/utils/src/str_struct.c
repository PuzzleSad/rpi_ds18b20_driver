#include "../str_utils.h"
#include "usefuldefines.h"

#include <linux/types.h>
#include <stdlib.h>
#include <string.h>

void su_stringarr_init(string_array_t* sa){
        memset( sa, 0, sizeof( string_array_t ) );
}       

int su_stringarr_insert( string_array_t* sa, const char* str ){
        size_t str_len;

        if(str == NULL){
                printerr_loc("Warning, input str arg is NULL");
                return 0;
        }


        str_len = strlen( str );

        if( str_len > MAX_STR_LEN ){
                print_stderr("Warning, stringarr arg size > max def str len\n");
                return 0;
        }

        sa->count++;
        sa->strarr = (char**)realloc( sa->strarr, sa->count * sizeof(char*) );

        sa->strarr[sa->count-1] = (char*)malloc( (str_len * sizeof(char)) + 1 );
        char* dest = sa->strarr[sa->count-1];
        
        memcpy( dest, str, str_len +1 );



        return 1;
}

void su_stringarr_fini( string_array_t* sa ){
        for( int i = 0; i < sa->count; i++ ){
                free(sa->strarr[i]);
        }

        free( sa->strarr );
}
