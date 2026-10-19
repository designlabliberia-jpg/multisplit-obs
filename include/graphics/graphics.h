#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gs_effect gs_effect_t;

void gs_matrix_push(void);
void gs_matrix_pop(void);
void gs_matrix_scale3f(float x, float y, float z);
void gs_matrix_translate3f(float x, float y, float z);
void gs_matrix_rotaa4f(float x, float y, float z, float angle);

#ifdef __cplusplus
}
#endif
