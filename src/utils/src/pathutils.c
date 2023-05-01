#include "../utils.h"
#include "usefuldefines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

static int write_copy( char** path, const char* to_copy );
static void access_fine_debug_print( const char* path );


int step_validatepath(const char* path){
        char* workingPath = NULL;
        char delim[2] = "/";
        char *token;


        if( path == NULL ){
                print_stderr("path to validate is NULL");
                return 0;
        }

        if( !write_copy( &workingPath, path ) ){
                return 0;
        }
        


        size_t str_len = strlen( workingPath );
        char path_rebuild[str_len + 1];
        int path_offset = 0;


        memset( path_rebuild, 0 , str_len+1 );
        


        token = strtok( workingPath, delim );

        while( token != NULL ){
                int token_len;
                path_rebuild[path_offset] = '/';
                path_offset++;

                token_len = strlen(token);
                memcpy( &path_rebuild[path_offset], token, token_len);
                path_offset += token_len;

                if( !validate_path(path_rebuild, R_OK ) ){
                     free(workingPath);         
                     return 0;
                }

                // printf("%s\n", path_rebuild);    //prints the path as its being rebuilt. Nice for debug

                token = strtok( NULL, delim );
        }


                      

        free(workingPath);
        return 1;
}




int validate_path( const char* path, int flags ){ //100 R, 010 W, 001 X
        if( access( path, F_OK) != 0 ){
                fprintf(stderr, "Error, file does not exist\nPath: %s\n", path);
                return 0;
        }

        if( access( path, flags ) != 0 ){
                access_fine_debug_print(path);
                return 0;
        }

        return 1;
}




static void access_fine_debug_print( const char* path ){
        fprintf(stderr, "File access permission issue for:\n%s\n", path);

        if( access( path, R_OK ) != 0 ){
                fprintf(stderr, "Read permission denied.\n");
        }
        if( access( path, W_OK ) != 0 ){
                fprintf(stderr, "Write permission denied.\n");
        }
}




static int write_copy( char** path, const char* to_copy ){
        size_t str_len;

        str_len = strlen( to_copy );

        if( str_len > LONGEST_STR ){    //something suspicious might be happening if path lengs get to >2k char len
                printerr_loc("strlen reported string length > longest acceptable string\n");
                fprintf(stderr, "Input len: %"PRIu64"\n", str_len );
                fprintf(stderr, "Longest acceptable str: %"PRId32"\n", LONGEST_STR );
                return 0;
        }

        *path = (char*)calloc(str_len +1, sizeof(char));
        memcpy( *path, to_copy, str_len );

        return 1;
}
