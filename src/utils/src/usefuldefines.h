#ifndef USEFULDEFINES_H
#define USEFULDEFINES_H

#include <stdio.h>



#define validate_return( status )\
do{\
        if( status != 1 ){\
                return 0;\
        }\
}while(0)



#define printerr_loc(errmsg)\
do{\
        fprintf(stderr, "\033[91m"errmsg"\033[0m");\
        fprintf(stderr, "\033[95m""func: %s\n""\033[0m", __FUNCTION__);\
        fprintf(stderr, "\033[95m""file: %s\n""\033[0m", __FILE__);\
        fprintf(stderr, "\033[95m""line: %d\n""\033[0m", __LINE__);\
}while(0)

#define print_stderr(errmsg)\
do{\
        fprintf(stderr, "\033[91m"errmsg"\033[0m");\
}while(0)

#endif
