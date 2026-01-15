#pragma once
#include "Constants.hpp"
#include <raylib.h>
#include <string>
#include "ErrorHandling.hpp"

class Window {
public:
	Window(int width = WINDOW_WIDTH,
		 int height = WINDOW_HEIGHT,
		 const std::string title = GAME_TITLE) {
		InitWindow(width, height, title.c_str());
		if(!IsWindowReady()) {
			throw std::runtime_error("Window failed to load.");
		}
		SetTargetFPS(TARGET_FPS);
		Width = width;
		Height = height;
	}
	~Window() { CloseWindow(); }

	bool shouldClose() const noexcept { return WindowShouldClose(); } // Detect window close button or ESC key
	Rectangle GetBounds() const noexcept { return Rectangle(0, 0, Width, Height); }
	int GetWidth() const noexcept { return Width = GetScreenWidth(); } //calculate window width / height if necessary
	int GetHeight() const noexcept { return Height = GetScreenHeight(); }

	static int Width;
	static int Height;
	
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};
