#ifndef LIBBCU_H
#define LIBBCU_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	LIBBCU_OK = 0,
	LIBBCU_ERR = -1,
	LIBBCU_ERR_INVALID_PARAM = -2,
	LIBBCU_ERR_IO = -3,
	LIBBCU_ERR_TIMEOUT = -4,
	LIBBCU_ERR_NOT_FOUND = -5,
	LIBBCU_ERR_UNSUPPORTED = -6,
} libbcu_status_t;

typedef enum {
	LIBBCU_LOG_INFO = 0,
	LIBBCU_LOG_ERROR = 1,
} libbcu_log_level_t;

typedef void (*libbcu_log_callback_t)(libbcu_log_level_t level, const char* message, void* user_data);

void libbcu_set_log_callback(libbcu_log_callback_t callback, void* user_data);

#ifdef __cplusplus
}
#endif

#endif
