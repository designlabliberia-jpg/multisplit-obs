#pragma once
#include "obsconfig.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct obs_video_info;
struct obs_audio_info;
struct obs_source;
struct obs_source_info;
struct obs_properties;
struct obs_property;
struct obs_data;
struct gs_effect;

typedef struct obs_source obs_source_t;
typedef struct obs_properties obs_properties_t;
typedef struct obs_property obs_property_t;
typedef struct obs_data obs_data_t;
typedef struct gs_effect gs_effect_t;

enum obs_source_type {
    OBS_SOURCE_TYPE_INPUT,
    OBS_SOURCE_TYPE_FILTER,
    OBS_SOURCE_TYPE_TRANSITION,
    OBS_SOURCE_TYPE_SCENE
};

enum obs_combo_type {
    OBS_COMBO_TYPE_INVALID,
    OBS_COMBO_TYPE_EDITABLE,
    OBS_COMBO_TYPE_LIST
};

enum obs_combo_format {
    OBS_COMBO_FORMAT_INVALID,
    OBS_COMBO_FORMAT_INT,
    OBS_COMBO_FORMAT_FLOAT,
    OBS_COMBO_FORMAT_STRING
};

enum {
    OBS_SOURCE_VIDEO = (1 << 0),
    OBS_SOURCE_AUDIO = (1 << 1),
    OBS_SOURCE_COMPOSITE = (1 << 2),
    OBS_SOURCE_DO_NOT_DUPLICATE = (1 << 3),
    OBS_SOURCE_CUSTOM_DRAW = (1 << 4),
    OBS_SOURCE_ASYNC = (1 << 5)
};

#define LOG_DEBUG 100
#define LOG_INFO 200
#define LOG_WARNING 300
#define LOG_ERROR 400

void blog(int log_level, const char *format, ...);

uint32_t obs_source_get_width(const obs_source_t *source);
uint32_t obs_source_get_height(const obs_source_t *source);
uint32_t obs_source_get_output_flags(const obs_source_t *source);
const char *obs_source_get_name(const obs_source_t *source);
void obs_source_video_render(obs_source_t *source);
void obs_register_source(struct obs_source_info *info);

obs_source_t *obs_get_source_by_name(const char *name);
void obs_source_release(obs_source_t *source);

obs_data_t *obs_source_get_settings(obs_source_t *source);
void obs_data_set_double(obs_data_t *data, const char *name, double val);
void obs_data_set_bool(obs_data_t *data, const char *name, bool val);
void obs_source_update(obs_source_t *source, obs_data_t *settings);
void obs_data_release(obs_data_t *data);
const char *obs_data_get_string(obs_data_t *data, const char *name);
double obs_data_get_double(obs_data_t *data, const char *name);
bool obs_data_get_bool(obs_data_t *data, const char *name);

obs_properties_t *obs_properties_create(void);
void obs_properties_destroy(obs_properties_t *props);
obs_property_t *obs_properties_add_list(obs_properties_t *props, const char *name, const char *description, enum obs_combo_type type, enum obs_combo_format format);
obs_property_t *obs_properties_add_button(obs_properties_t *props, const char *name, const char *text, bool (*callback)(obs_properties_t *props, obs_property_t *property, void *data));
obs_property_t *obs_properties_add_float_slider(obs_properties_t *props, const char *name, const char *text, double min, double max, double step);
obs_property_t *obs_properties_add_bool(obs_properties_t *props, const char *name, const char *text);
bool obs_property_list_add_string(obs_property_t *p, const char *name, const char *val);

void obs_enum_sources(bool (*enum_callback)(void *param, obs_source_t *source), void *param);

struct obs_source_info {
    const char *id;
    enum obs_source_type type;
    uint32_t output_flags;
    const char *(*get_name)(void *data);
    void *(*create)(obs_data_t *settings, obs_source_t *source);
    void (*destroy)(void *data);
    uint32_t (*get_width)(void *data);
    uint32_t (*get_height)(void *data);
    void (*video_render)(void *data, gs_effect_t *effect);
    void (*video_tick)(void *data, float seconds);
    void (*get_defaults)(obs_data_t *settings);
    obs_properties_t *(*get_properties)(void *data);
    void (*update)(void *data, obs_data_t *settings);
};

#ifdef __cplusplus
}
#endif
