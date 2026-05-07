#ifndef LIBBCU_SILENT_H
#define LIBBCU_SILENT_H

#include <stdio.h>

#ifdef LIBBCU_NO_PRINT
#define BCU_PRINTF(...) ((int)0)
#define BCU_FPRINTF(...) ((int)0)
#else
#define BCU_PRINTF(...) printf(__VA_ARGS__)
#define BCU_FPRINTF(...) fprintf(__VA_ARGS__)
#endif

#endif
