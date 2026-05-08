#ifndef LIBBCU_SILENT_H
#define LIBBCU_SILENT_H

#include <stdio.h>
#include "libbcu/libbcu.h"

void libbcu_log_message(libbcu_log_level_t level, const char* format, ...);

#ifdef LIBBCU_NO_PRINT
#define BCU_PRINTF(...) ((int)0)
#define BCU_FPRINTF(...) ((int)0)
#else
#define BCU_PRINTF(...) printf(__VA_ARGS__)
#define BCU_FPRINTF(...) fprintf(__VA_ARGS__)
#endif

#define BCU_APP_LOG_INFO(...) libbcu_log_message(LIBBCU_LOG_INFO, __VA_ARGS__)
#define BCU_APP_LOG_ERROR(...) libbcu_log_message(LIBBCU_LOG_ERROR, __VA_ARGS__)

#endif
