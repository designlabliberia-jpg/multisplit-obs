#pragma once
#include <obs-module.h>
#include "source-manager.hpp"

struct MultiSplitSource {
    obs_source_t* context;
    SourceManager source_manager;
    
    // Framing state
    float center_x = 0.5f;
    float center_y = 0.5f;
    float zoom = 1.0f;
    float rotation = 0.0f;
    bool flip_h = false;
    bool flip_v = false;
};
