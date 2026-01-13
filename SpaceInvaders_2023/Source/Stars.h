#pragma once
#include <raylib.h>
#include "Constants.h"

struct Star {
	explicit Star() {
		position.x = GetRandomValue(-BACKGROUND_EDGE_X, GetScreenWidth() + BACKGROUND_EDGE_X);
		position.y = GetRandomValue(0, GetScreenHeight());
		circle = Circle(position, GetRandomValue(1, 4) / 2.0f);
	}
	float getSize() { return circle.radius; }
	Circle getRenderCircle() { return Circle(position + Vector2(offsetX, 0), circle.radius);}
	void Render(Renderer& renderer) { renderer.Render(getRenderCircle(), STAR_COLOR); }
	static float offsetX;
private:
	Vector2 position;
	Circle circle;
};
