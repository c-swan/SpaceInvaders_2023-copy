#pragma once
#include <string>
#include <raylib.h>
#include "Math.hpp"

static constexpr std::string GAME_TITLE = "SPACE INVADERS";
static constexpr int APP_QUIT_CODE = 0;

static constexpr int SCREEN_WIDTH = 1920;
static constexpr int SCREEN_HEIGHT = 1080;

static constexpr std::string ASSETS_DIRECTORY = "./Assets/";

static constexpr int ALIEN_FORMATION_WIDTH = 8;
static constexpr int ALIEN_FORMATION_HEIGHT = 5;
static constexpr float ALIEN_SPACING = 80;
static constexpr Vector2 ALIEN_FORMATION_POS = {100, 50};

static constexpr int WALL_COUNT = 5;

static constexpr int SHIP_TEXTURE_COUNT = 3;

static constexpr Color DEFAULT_FONT_COLOR = YELLOW;

static constexpr int TITLE_FONT_SIZE = 60;
static constexpr int DEFAULT_FONT_SIZE = 40;
static constexpr int HALF_FONT_SIZE = DEFAULT_FONT_SIZE / 2;

static constexpr float PLAYER_BASE_HEIGHT = 70.0f;
