#pragma once
#include <string>
#include <raylib.h>
#include "Math.hpp"

static constexpr int SCREEN_WIDTH = 1920;
static constexpr int SCREEN_HEIGHT = 1080;

static constexpr std::string ASSETS_DIR = "./Assets/";

static constexpr int ALIEN_FORMATION_WIDTH = 8;
static constexpr int ALIEN_FORMATION_HEIGHT = 5;
static constexpr float ALIEN_SPACING = 80;
static constexpr Vector2 ALIEN_FORMATION_POS = {100, 50};

static constexpr int WALL_COUNT = 5;
