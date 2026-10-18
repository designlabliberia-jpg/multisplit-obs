#pragma once
extern "C" {
#include <obs-source.h>
}
#include "crop-math.hpp"

class CropRenderer {
public:
	static void Render(obs_source_t *source, const CropRect::PixelRect &rect);
};
