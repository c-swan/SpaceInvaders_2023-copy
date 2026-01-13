#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Window.hpp"
#include "Entities.hpp"
#include "Math.h"


class Renderer {
public:
	Renderer(const Window& window) : bounds(0,0, window.GetWidth(), window.GetHeight()) { }
	~Renderer() {}

	void Render(Texture2D* texture, Rectangle& bounds, Vector2& position)  {
		DrawTexturePro(*texture, ::getRect(texture->width, texture->height), bounds + position, Vector2(bounds.width, bounds.height) / 2, NO_ROTATION, NO_TINT);
	}
	void Render(const Circle& circle, const Color& color) noexcept { DrawCircle(circle.center.x, circle.center.y, circle.radius, color); }
	void Render(const Rectangle& rect, const Color& color) { ::DrawRectangleRec(rect, color); }

	void DrawText(std::string text, Vector2 pos, int fontSize = DEFAULT_FONT_SIZE, Color fontColor = DEFAULT_FONT_COLOR) { ::DrawText(text.c_str(), pos.x, pos.y, fontSize, fontColor); }

	float GetWidth() const noexcept { return bounds.width; }
	float GetHeight() const noexcept { return bounds.height; }
private:
	Rectangle bounds;
};

