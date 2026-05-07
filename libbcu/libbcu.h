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

#ifdef __cplusplus
}
#endif

#endif
