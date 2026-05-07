#ifndef LIBBCU_SILENT_H
#define LIBBCU_SILENT_H

#include <stdarg.h>
#include <stdio.h>

#ifdef LIBBCU_NO_PRINT
static inline int bcu_log_printf(const char* fmt, ...)
{
	/* No-print mode: preserve call sites, always return 0. */
	(void)fmt;
	return 0;
}

static inline int bcu_log_fprintf(FILE* stream, const char* fmt, ...)
{
	/* No-print mode: preserve call sites, always return 0. */
	(void)stream;
	(void)fmt;
	return 0;
}
#else
static inline int bcu_log_printf(const char* fmt, ...)
{
	va_list args;
	int ret;
	va_start(args, fmt);
	ret = vprintf(fmt, args);
	va_end(args);
	return ret;
}

static inline int bcu_log_fprintf(FILE* stream, const char* fmt, ...)
{
	va_list args;
	int ret;
	va_start(args, fmt);
	ret = vfprintf(stream, fmt, args);
	va_end(args);
	return ret;
}
#endif

#define BCU_PRINTF(...) bcu_log_printf(__VA_ARGS__)
#define BCU_FPRINTF(...) bcu_log_fprintf(__VA_ARGS__)

#endif
