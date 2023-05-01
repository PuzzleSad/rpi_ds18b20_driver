#include "msr_ds18b20.h"
#include "src/utils/utils.h"
#include "src/utils/str_utils.h"
#include "src/ds18b20/ds18b20.h"
#include "src/read_thread/read_thread.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void strarr_test();
void ds_test();
void read_thread_test();

int main(){

        printf("Test\n");
        // strarr_test();
        ds_test();
        
        // step_validatepath( "/sys/bus/w1/devices/28-3c01f095aa1f/id" );

        // fread_oneshot()
        
        // read_thread_test();


}

void fread_oneshot(){
        FILE* fp = fopen( "/sys/bus/w1/devices/28-3c01f095aa1f/id", "r");
        uint64_t num;
        fread( &num, sizeof(uint64_t), 1, fp );
        printf("%lx\n", num );
        fclose(fp);
}

void ds_test(){
        string_array_t* sa;
        sa = ds_possible_sensors( NULL );

        su_stringarr_printall( sa );

        su_stringarr_fini( sa );
        free(sa);

        // uint64_t res = ds_get_serial("/sys/bus/w1/devices/28-3c01f095aa1f");
        ds18b20_t ds;
        init_ds18b20( &ds, "/sys/bus/w1/devices/28-3c01f095aa1f" );

        printf("xPath: %s\n", ds.path );
        printf("xSerial: %lx\n", ds.serial_number );

        


        ds18b20_collection_t ds_collect;
        init_ds18b20_collection( &ds_collect );

        ds_collection_append( &ds_collect, &ds );
        ds_collection_printall( &ds_collect );


        printf("splice: %s\n", ds_splice_path( ds.path, "lmao" ) );

        fini_ds18b20( &ds );
        fini_ds18b20_collection( &ds_collect );

        
        
}

void strarr_test(){
        string_array_t sa;
        su_stringarr_init( &sa );
        su_stringarr_insert( &sa, "word" );

        printf("%s\n", sa.strarr[0]);

        su_stringarr_fini( &sa );
}

void read_thread_test(){
        ds_reader_t dr;
        ds_reader_init( &dr );




        ds_reader_fini( &dr );
}
