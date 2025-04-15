#ifndef TOOLS_H
#define TOOLS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define END         "\033[0;0m"                             //* Add colour outputs in my program :)
#define RED_CLR     "\033[1;31m"
#define GREEN_CLR   "\033[1;32m"
#define RED(str)     RED_CLR     str END
#define GREEN(str)   GREEN_CLR   str END

#define FREE(object) { free(object); (object) = NULL; }     //* Proper release of dynamic memory

typedef enum ReturnCodes {
    SUCCESS      =  0,
    MEMORY_ERROR = -1,
    FILE_ERROR   = -2
} ReturnCodes;

#endif // TOOLS_H