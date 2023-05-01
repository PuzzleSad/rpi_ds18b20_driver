#include "msr_ds18b20.h"
#include "src/utils/utils.h"
#include "src/utils/str_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void strarr_test();

int main(){

        printf("Test\n");
        // strarr_test();

        
        // step_validatepath( "/sys/bus/w1/devices/28-3c01f095aa1f/id" );


        FILE* fp = fopen( "/sys/bus/w1/devices/28-3c01f095aa1f/id", "r");
        char str[100]; //Thumbsuck number
        memset( str, 0, 100);

        fscanf( fp, "%s", str );

        /* Remembering that it printed garbage, lets see what happens if we print the values of each byte */
        /* Additionally, due to the nature of a little endian system, let's print the bytes in reverse  */

        for(int i = 7; i >= 0; i--){
                printf("%x ", (int) str[i] );
        } 
        printf("\n");



        fclose(fp);



}


void strarr_test(){
        string_array_t sa;
        su_stringarr_init( &sa );
        su_stringarr_insert( &sa, "word" );

        printf("%s\n", sa.strarr[0]);

        su_stringarr_fini( &sa );
}
