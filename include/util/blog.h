#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define LOG_INFO 100
#define LOG_WARNING 200
#define LOG_ERROR 300

void blog(int log_level, const char* format, ...);

#ifdef __cplusplus
}
#endif
