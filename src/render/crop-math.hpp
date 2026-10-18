#pragma once
#include <cstdint>

struct CropRect {
    float center_x; // 0.0 to 1.0
    float center_y; // 0.0 to 1.0
    float zoom;     // 1.0 = native, >1.0 = zoomed

    struct PixelRect {
        int32_t x;
        int32_t y;
        int32_t width;
        int32_t height;
    };

    static PixelRect GetPixelRect(uint32_t source_width, uint32_t source_height, 
                                  float center_x, float center_y, float zoom);
};
