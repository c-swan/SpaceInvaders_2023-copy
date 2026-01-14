#pragma once
#include <raylib.h>
#include <string>
#include "Constants.h"

struct TextUI {
	TextUI() {}
	TextUI(std::string str, Vector2 pos) : text(str), position(pos) {}
	TextUI(std::string str, Vector2 pos, int size) : text(str), position(pos), fontSize(size) {}
	TextUI(std::string str, Vector2 pos, int size, Color color) : text(str), position(pos), fontSize(size), fontColor(color) {}
	TextUI(std::string str, Vector2 pos, Color color) : text(str), position(pos), fontColor(color) {}

	std::string text = "";
	Vector2 position = {0,0};
	int fontSize = DEFAULT_FONT_SIZE;
	Color fontColor = DEFAULT_FONT_COLOR;
};
