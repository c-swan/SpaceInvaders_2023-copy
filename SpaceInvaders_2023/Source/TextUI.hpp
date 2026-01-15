#pragma once
#include <raylib.h>
#include <string>
#include "Constants.hpp"

struct TextUI {
	TextUI() = default;
	TextUI(std::string str, Vector2 pos) : text(str), position(pos) {}
	TextUI(std::string str, Vector2 pos, int size) : text(str), position(pos), fontSize(size) {}
	TextUI(std::string str, Vector2 pos, int size, Color color) : text(str), position(pos), fontSize(size), fontColor(color) {}
	TextUI(std::string str, Vector2 pos, Color color) : text(str), position(pos), fontColor(color) {}

	std::string text = "";
	Vector2 position = {0,0};
	int fontSize = DEFAULT_FONT_SIZE;
	Color fontColor = DEFAULT_FONT_COLOR;
	Vector2 offset = {0,0};

	int GetWidth() const noexcept { return MeasureText(text.c_str(), fontSize); }

	void CenterAlign() { offset.x = -GetWidth() / 2; }
	void LeftAlign() { offset.x = 0; }
	void RightAlign() { offset.x = - GetWidth(); }
	void VerticalAlign() { offset.y = - fontSize / 2; }
};
