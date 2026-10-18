#include "crop-math.hpp"
#include <algorithm>

CropRect::PixelRect CropRect::GetPixelRect(uint32_t source_width, uint32_t source_height,
                                          float center_x, float center_y, float zoom) {
    float crop_width = static_cast<float>(source_width) / zoom;
    float crop_height = static_cast<float>(source_height) / zoom;

    float left = (center_x * source_width) - (crop_width / 2.0f);
    float top = (center_y * source_height) - (crop_height / 2.0f);

    // Clamp to bounds
    left = std::max(0.0f, std::min(left, static_cast<float>(source_width) - crop_width));
    top = std::max(0.0f, std::min(top, static_cast<float>(source_height) - crop_height));

    return {
        static_cast<int32_t>(left),
        static_cast<int32_t>(top),
        static_cast<int32_t>(crop_width),
        static_cast<int32_t>(crop_height)
    };
}
