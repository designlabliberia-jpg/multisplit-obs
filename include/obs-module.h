#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define OBS_IMPORT __declspec(dllimport)
#else
#define OBS_IMPORT
#endif

OBS_IMPORT bool obs_register_module(void *module);

#define OBS_DECLARE_MODULE() \
    const char *obs_module_name(void) { return "multisplit"; }

#define OBS_MODULE_USE_DEFAULT_LOCALE(name, locale)

#ifdef __cplusplus
}
#endif
