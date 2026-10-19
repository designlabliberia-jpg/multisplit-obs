#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define OBS_IMPORT __declspec(dllimport)
#else
#define OBS_IMPORT
#endif

#define LOG_INFO 100
#define LOG_WARNING 200
#define LOG_ERROR 300

OBS_IMPORT void blog(int log_level, const char* format, ...);

#ifdef __cplusplus
}
#endif
