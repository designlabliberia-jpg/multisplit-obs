#include "crop-renderer.hpp"
#include <graphics/graphics.h>
#include <obs-source.h>

void CropRenderer::Render(obs_source_t* source, const CropRect::PixelRect& rect) {
    if (!source) return;

    gs_matrix_push();

    uint32_t w = obs_source_get_width(source);
    uint32_t h = obs_source_get_height(source);

    if (rect.width > 0 && rect.height > 0 && w > 0 && h > 0) {
        float zoom_x = static_cast<float>(w) / static_cast<float>(rect.width);
        float zoom_y = static_cast<float>(h) / static_cast<float>(rect.height);

        gs_matrix_scale3f(zoom_x, zoom_y, 1.0f);
        gs_matrix_translate3f(static_cast<float>(-rect.x), static_cast<float>(-rect.y), 0.0f);
    }

    obs_source_video_render(source);

    gs_matrix_pop();
}
