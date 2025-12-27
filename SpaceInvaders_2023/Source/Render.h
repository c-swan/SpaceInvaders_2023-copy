//
//  Render.h
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-22.
//

#ifndef Render_h
#define Render_h
#include <string>
#include "raylib.h"
#include "Math.hpp"

namespace Render {
	//	using c_string_type = const char *;
	using string_type = std::string;

	inline void DrawRectangleLines(float x, float y, float width, float height, Color inputFieldColor) { ::DrawRectangleLines(x, y, width, height, inputFieldColor); }
	inline void DrawRectangleLines(Rectangle &rect, Color inputFieldColor) { DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, inputFieldColor); }
	inline void DrawText(string_type text, const Rectangle& bounds, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { DrawText(text.c_str(), bounds.x, bounds.y , fontSize, color); }
	inline void DrawText(string_type text, const Vector2& pos, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { DrawText(text.c_str(), pos.x, pos.y , fontSize, color); }
	inline void DrawTextCounter(string_type text, float value, const Vector2& pos, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { DrawText(std::format("{}: {}", text, value).c_str(), pos.x, pos.y , fontSize, color); }
//	inline void DrawText(string_type text, float x, float y, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { ::DrawText(text.c_str(), x, y, fontSize, color); }

	inline void DrawTextCentered(string_type text, Vector2& pos, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { DrawText(text, pos + (Vector2(MeasureText(text.c_str(), fontSize), fontSize) / -2), fontSize, color); }
	inline void DrawTextCentered(string_type text, const Rectangle& bounds, int fontSize = DEFAULT_FONT_SIZE, Color color = DEFAULT_FONT_COLOR) { DrawText(text, bounds + (Vector2(MeasureText(text.c_str(), fontSize), fontSize) / -2), fontSize, color); }
};
#endif /* Render_h */
