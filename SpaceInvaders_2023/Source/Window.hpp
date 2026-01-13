#pragma once
#include "Constants.h"
#include <raylib.h>

class Window {
public:
	Window(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT, const std::string title = GAME_TITLE) {
		InitWindow(width, height, title.c_str());
	}
	~Window() { CloseWindow(); }

	bool shouldClose() const noexcept { return WindowShouldClose(); } // Detect window close button or ESC key
	int GetWidth() const noexcept { return GetScreenWidth(); }
	int GetHeight() const noexcept { return GetScreenHeight(); }

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};
