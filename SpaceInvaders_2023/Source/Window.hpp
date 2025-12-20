//
//  Window.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef Window_hpp
#define Window_hpp
#include "Constants.h"
#include <raylib.h>

class Window {
public:
	Window() { InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SPACE INVADERS");  }
	~Window() { CloseWindow(); }

	bool shouldClose() const { return WindowShouldClose(); }

private:
	

};
#endif /* Window_hpp */
