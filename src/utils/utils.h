#ifndef UTILS_H
#define UTILS_H

#define LONGEST_STR 2000

#define UTILS_R 4
#define UTILS_W 2
#define UTILS_X 1

//Validate a path one dir at a time. Very useful for determining where the search breaks.
int step_validatepath(const char* path);
int validate_path( const char* path, int flags );       //use R_OK, W_OK, X_OK.  OR'd together

#endif
