#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Math.h"

struct Star {
	explicit Star() {
		circle.center.x = GetRandomValue(-BACKGROUND_EDGE_X, Window::Width + BACKGROUND_EDGE_X);
		circle.center.y = GetRandomValue(0, Window::Height);
		circle.radius = GetRandomValue(STAR_SIZE_MIN, STAR_SIZE_MAX) / 2;
	}
	void Render(Renderer& renderer) { renderer.Render(circle + Vector2(offset_x, 0), STAR_COLOR); }
	static float offset_x;
private:
	Circle circle;
};
