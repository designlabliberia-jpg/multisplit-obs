#include "multisplit-source.hpp"
#include <obs-source.h>
#include <graphics/effect.h>
#include "render/crop-renderer.hpp"
#include "render/crop-math.hpp"
#include "render/transform.hpp"
#include "diagnostics/performance-monitor.hpp"
#include "presets/preset-manager.hpp"

// Forward declare for the render function
void ApplyTransform(const TransformState& state, float center_x, float center_y);
void EndTransform();

static const char* multisplit_get_name(void* data) {
    (void)data;
    return "Multi Split View";
}

static bool reset_preset_clicked(obs_properties_t* props, obs_property_t* p, void* data) {
    (void)props;
    (void)p;
    MultiSplitSource* s = static_cast<MultiSplitSource*>(data);
    if (s && s->context) {
        obs_data_t* settings = obs_source_get_settings(s->context);
        if (settings) {
            obs_data_set_double(settings, "center_x", 50.0);
            obs_data_set_double(settings, "center_y", 50.0);
            obs_data_set_double(settings, "zoom", 1.0);
            obs_data_set_double(settings, "rotation", 0.0);
            obs_data_set_bool(settings, "flip_h", false);
            obs_data_set_bool(settings, "flip_v", false);
            obs_source_update(s->context, settings);
            obs_data_release(settings);
        }
    }
    return true;
}

static bool save_preset_clicked(obs_properties_t* props, obs_property_t* p, void* data) {
    (void)props;
    (void)p;
    MultiSplitSource* s = static_cast<MultiSplitSource*>(data);
    if (s) {
        Preset p_obj{"Custom Preset", s->center_x, s->center_y, s->zoom, s->rotation, s->flip_h, s->flip_v};
        std::string json = PresetManager::Serialize(p_obj);
        blog(LOG_INFO, "Saved preset JSON: %s", json.c_str());
    }
    return true;
}

static obs_properties_t* multisplit_get_properties(void* data) {
    obs_properties_t* props = obs_properties_create();
    
    // Preset controls
    obs_properties_add_list(props, "preset_list", "Load Preset", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
    obs_properties_add_button(props, "save_preset", "Save as New", save_preset_clicked);
    obs_properties_add_button(props, "reset_preset", "Reset to Default", reset_preset_clicked);

    obs_property_t* source_list = obs_properties_add_list(props, "input_source", "Base Camera Source", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);

    auto add_source = [](void* data, obs_source_t* source) {
        obs_property_t* p = static_cast<obs_property_t*>(data);
        if (obs_source_get_output_flags(source) & OBS_SOURCE_VIDEO) {
            obs_property_list_add_string(p, obs_source_get_name(source), obs_source_get_name(source));
        }
        return true;
    };
    obs_enum_sources(add_source, source_list);

    obs_properties_add_float_slider(props, "center_x", "Center X (%)", 0.0, 100.0, 0.1);
    obs_properties_add_float_slider(props, "center_y", "Center Y (%)", 0.0, 100.0, 0.1);
    obs_properties_add_float_slider(props, "zoom", "Zoom (x)", 1.0, 4.0, 0.1);
    obs_properties_add_float_slider(props, "rotation", "Rotation (°)", -180.0, 180.0, 1.0);
    obs_properties_add_bool(props, "flip_h", "Flip Horizontal");
    obs_properties_add_bool(props, "flip_v", "Flip Vertical");
    
    return props;
}

static void multisplit_update(void* data, obs_data_t* settings) {
    MultiSplitSource* s = static_cast<MultiSplitSource*>(data);
    const char* source_name = obs_data_get_string(settings, "input_source");
    s->source_manager.set_source(source_name);
    
    s->center_x = (float)obs_data_get_double(settings, "center_x") / 100.0f;
    s->center_y = (float)obs_data_get_double(settings, "center_y") / 100.0f;
    s->zoom = (float)obs_data_get_double(settings, "zoom");
    s->rotation = (float)obs_data_get_double(settings, "rotation");
    s->flip_h = obs_data_get_bool(settings, "flip_h");
    s->flip_v = obs_data_get_bool(settings, "flip_v");
}

static void* multisplit_create(obs_data_t* settings, obs_source_t* source) {
    MultiSplitSource* data = new MultiSplitSource();
    data->context = source;
    multisplit_update(data, settings);
    return data;
}

static void multisplit_destroy(void* data) {
    MultiSplitSource* s = static_cast<MultiSplitSource*>(data);
    delete s;
}

static uint32_t multisplit_get_width(void* data) {
    return 1920; 
}

static uint32_t multisplit_get_height(void* data) {
    return 1080;
}

static void multisplit_video_render(void* data, gs_effect_t* effect) {
    PerformanceMonitor perf;
    perf.Start();

    MultiSplitSource* s = static_cast<MultiSplitSource*>(data);
    obs_source_t* base_source = s->source_manager.get_source();
    
    if (base_source) {
        uint32_t w = obs_source_get_width(base_source);
        uint32_t h = obs_source_get_height(base_source);
        
        CropRect::PixelRect rect = CropRect::GetPixelRect(w, h, s->center_x, s->center_y, s->zoom);
        
        // Apply transform
        TransformState t = { s->rotation, s->flip_h, s->flip_v };
        ApplyTransform(t, s->center_x, s->center_y);
        
        CropRenderer::Render(base_source, rect);
        
        EndTransform();
    } else {
        // No base source selected yet - render nothing or black background
    }

    double render_time = perf.EndAndGetMilliseconds();
    if (render_time > 5.0) { // Log if slow
        blog(LOG_WARNING, "MultiSplit render slow: %.2fms", render_time);
    }
}

struct obs_source_info multisplit_source_info = {
    .id = "multisplit_view",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_CUSTOM_DRAW,
    .get_name = multisplit_get_name,
    .create = multisplit_create,
    .destroy = multisplit_destroy,
    .get_width = multisplit_get_width,
    .get_height = multisplit_get_height,
    .video_render = multisplit_video_render,
    .get_properties = multisplit_get_properties,
    .update = multisplit_update
};
