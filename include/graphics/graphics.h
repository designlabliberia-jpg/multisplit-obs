#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define OBS_IMPORT __declspec(dllimport)
#else
#define OBS_IMPORT
#endif

typedef struct gs_effect gs_effect_t;

OBS_IMPORT void gs_matrix_push(void);
OBS_IMPORT void gs_matrix_pop(void);
OBS_IMPORT void gs_matrix_scale3f(float x, float y, float z);
OBS_IMPORT void gs_matrix_translate3f(float x, float y, float z);
OBS_IMPORT void gs_matrix_rotaa4f(float x, float y, float z, float angle);

#ifdef __cplusplus
}
#endif
