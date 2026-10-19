#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define OBS_IMPORT __declspec(dllimport)
#define OBS_EXPORT __declspec(dllexport)
#else
#define OBS_IMPORT
#define OBS_EXPORT
#endif

OBS_IMPORT bool obs_register_module(void *module);

#define OBS_DECLARE_MODULE() \
    OBS_EXPORT const char *obs_module_name(void)

#define OBS_MODULE_USE_DEFAULT_LOCALE(name, locale)

#ifdef __cplusplus
}
#endif
