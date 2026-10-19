#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <obs.h>
#include <obs-source.h>
#include <obs-module.h>

typedef bool (*obs_source_enum_proc_t)(void *param, obs_source_t *parent, obs_source_t *child, void *private_param);

#ifdef __cplusplus
}
#endif
