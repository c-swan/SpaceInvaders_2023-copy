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



namespace Render {
	using string_type = const char *;
//	using string_type = std::string&;

	
	inline void DrawTextCenteredHorizontal(string_type text, int posY, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR) {
		int halfTextWidth = MeasureText(text, fontSize) / 2;
		DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, posY, fontSize, color);
	}

	inline void DrawTextCentered(string_type text, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR) {        // Draw text (using default font)
		int halfTextWidth = MeasureText(text, fontSize) / 2;
		DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, WINDOW_HEIGHT / 2, fontSize, color);
	}

//	inline void DrawTextCentered(string_type text, Vector2 offset, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR) {
//		int halfTextWidth = MeasureText(text, fontSize) / 2;
//		DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth + offset.x, WINDOW_HEIGHT / 2 + offset.y, fontSize, color);
//	}
};

#endif /* Render_h */
