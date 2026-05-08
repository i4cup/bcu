#include <stdarg.h>
#include <stdio.h>
#include "libbcu/libbcu.h"

#define LIBBCU_LOG_BUFFER_SIZE 512

static libbcu_log_callback_t g_libbcu_log_callback = NULL;
static void* g_libbcu_log_user_data = NULL;

void libbcu_set_log_callback(libbcu_log_callback_t callback, void* user_data)
{
	g_libbcu_log_callback = callback;
	g_libbcu_log_user_data = user_data;
}

void libbcu_log_message(libbcu_log_level_t level, const char* format, ...)
{
	char message[LIBBCU_LOG_BUFFER_SIZE];
	va_list args;

	if (g_libbcu_log_callback == NULL || format == NULL)
	{
		return;
	}

	va_start(args, format);
	vsnprintf(message, sizeof(message), format, args);
	va_end(args);

	g_libbcu_log_callback(level, message, g_libbcu_log_user_data);
}
