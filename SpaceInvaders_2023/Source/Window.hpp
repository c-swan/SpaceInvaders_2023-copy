//
//  Window.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.

#ifndef Window_hpp
#define Window_hpp

#include "Constants.h"
#include <raylib.h>
#include "Renderer.hpp"
class Window {
public:
	Window() {
		InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SPACE INVADERS");
	}
	~Window() {
		CloseWindow();
	}

	bool shouldClose() const { return WindowShouldClose(); }

	
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};
#endif /* Window_hpp */
