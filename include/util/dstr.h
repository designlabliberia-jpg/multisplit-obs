#pragma once
#ifdef __cplusplus
extern "C" {
#endif
struct dstr {
    char *array;
    size_t len;
    size_t capacity;
};
#ifdef __cplusplus
}
#endif
