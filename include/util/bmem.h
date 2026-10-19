#pragma once
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
void *bmalloc(size_t size);
void bfree(void *ptr);
#ifdef __cplusplus
}
#endif
