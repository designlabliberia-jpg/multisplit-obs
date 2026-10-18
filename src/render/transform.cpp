#include "transform.hpp"
#include <graphics/graphics.h>
#include <cmath>

void ApplyTransform(const TransformState &state, float center_x, float center_y)
{
	(void)center_x;
	(void)center_y;
	gs_matrix_push();

	// Scale for flipping
	float scale_x = state.flip_h ? -1.0f : 1.0f;
	float scale_y = state.flip_v ? -1.0f : 1.0f;

	// Rotate around Z axis using OBS function gs_matrix_rotaa4f(x, y, z, angle)
	float angle_rad = state.rotation * (3.14159265f / 180.0f);
	gs_matrix_rotaa4f(0.0f, 0.0f, 1.0f, angle_rad);

	// Apply scale after rotation
	gs_matrix_scale3f(scale_x, scale_y, 1.0f);
}

void EndTransform()
{
	gs_matrix_pop();
}
