#ifndef DEBUG_H
#define DEBUG_H

#define DO_DEBUG

#if defined(DO_DEBUG)
    #define DEBUG(str) str
#else
    #define DEBUG(str)
#endif

#if defined(DO_DEBUG)
    #include <stdio.h>
    #define print_error(format, ...) printf("Error in %s(): ", __func__); printf(format, ##__VA_ARGS__);
#endif


#define PRINT_LINE printf("Line: %d\n", __LINE__);

#endif // DEBUG_H