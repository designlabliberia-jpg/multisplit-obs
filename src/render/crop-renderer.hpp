#pragma once
#include "../obs-compat.hpp"
#include "crop-math.hpp"

class CropRenderer {
public:
	static void Render(obs_source_t *source, const CropRect::PixelRect &rect);
};
