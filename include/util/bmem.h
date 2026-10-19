#pragma once
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define OBS_IMPORT __declspec(dllimport)
#else
#define OBS_IMPORT
#endif

OBS_IMPORT void *bmalloc(size_t size);
OBS_IMPORT void bfree(void *ptr);

#ifdef __cplusplus
}
#endif
