#ifndef STR_UTILS_H
#define STR_UTILS_H

#define MAX_STR_LEN 2000        //set to whatever constraint you desire

typedef struct string_array_t{
        int count;
        char** strarr;
}string_array_t;

void su_stringarr_init(string_array_t* sa);
void su_stringarr_fini( string_array_t* sa );
int su_stringarr_insert( string_array_t* sa, const char* str );

#endif
