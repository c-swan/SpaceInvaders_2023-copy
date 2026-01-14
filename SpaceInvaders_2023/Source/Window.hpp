#pragma once
#include "Constants.h"
#include <raylib.h>

class Window {
public:
	Window(int width = WINDOW_WIDTH,
		 int height = WINDOW_HEIGHT,
		 const std::string title = GAME_TITLE) {
		InitWindow(width, height, title.c_str());
		Width = width;
		Height = height;
	}
	~Window() { CloseWindow(); }

	bool shouldClose() const noexcept { return WindowShouldClose(); } // Detect window close button or ESC key
	int GetWidth() const noexcept { return Width = GetScreenWidth(); } //calculate window width / height if necessary
	int GetHeight() const noexcept { return Height = GetScreenHeight(); }

	static int Width;
	static int Height;
	
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};
