#pragma once
#include "Constants.h"
#include <raylib.h>

class Window {
public:
	Window() {
		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SPACE INVADERS");
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

