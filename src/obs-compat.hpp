#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations to satisfy C++ strictness with libobs C headers
enum obs_source_type : int;
enum obs_media_state : int;
enum obs_icon_type : int;

struct obs_source;
typedef struct obs_source obs_source_t;

typedef bool (*obs_source_enum_proc_t)(void *param, obs_source_t *parent, obs_source_t *child, void *private_param);

#include <obs.h>
#include <obs-source.h>
#include <obs-module.h>

#ifdef __cplusplus
}
#endif
