#pragma once
#include <string>
#include <raylib.h>
#include "Math.h"

static constexpr int FPS = 60;
static constexpr std::string GAME_TITLE = "SPACE INVADERS";
static constexpr int APP_QUIT_CODE = 0;

static constexpr int SCREEN_WIDTH = 1920;
static constexpr int SCREEN_HEIGHT = 1080;

static constexpr std::string ASSETS_DIRECTORY = "./Assets/";

static constexpr int ALIEN_FORMATION_WIDTH = 8;
static constexpr int ALIEN_FORMATION_HEIGHT = 5;
static constexpr float ALIEN_SPACING = 80;
static constexpr Vector2 ALIEN_FORMATION_POS = {100, 50};

static constexpr int BUNKER_COUNT = 5;
static constexpr int BUNKER_MAX_HEALTH = 50;
static constexpr Color BUNKER_TEXT_COLOR = RED;
static constexpr float BUNKER_RADIUS = 60;
static constexpr int BUNKER_POSITION_Y = 250;
static constexpr int SHIP_TEXTURE_COUNT = 3;

static constexpr Color DEFAULT_FONT_COLOR = YELLOW;

static constexpr int TITLE_FONT_SIZE = 60;
static constexpr int DEFAULT_FONT_SIZE = 40;
static constexpr int HALF_FONT_SIZE = DEFAULT_FONT_SIZE / 2;

static constexpr float PLAYER_BASE_HEIGHT = 70.0f;
static constexpr float PLAYER_SPEED = 7; 
static constexpr int PLAYER_RADIUS = 50;
static constexpr int PLAYER_MAX_LIVES = 3;

static constexpr int ALIEN_SPEED = 2;
static constexpr float ALIEN_RADIUS = 30;
static constexpr int ALIEN_OFFSET_X = 450;
static constexpr int ALIEN_HIT_SCORE = 100;

static constexpr int STAR_COUNT = 600;
static constexpr int BACKGROUND_EDGE_X = 150;
static constexpr Color STAR_COLOR = SKYBLUE;

static constexpr int NO_ROTATION = 0;
static constexpr Color NO_TINT = WHITE;

static constexpr Color BACKGROUND_COLOR = BLACK;
static constexpr float LASER_SPEED = 15;
static constexpr float PROJECTILE_HEIGHT = 30;
static constexpr float PROJECTILE_WIDTH = 6;
static constexpr float PLAYER_ANIMATION_FRAME_DURATION = 0.4;
static constexpr float PARALLAX_FACTOR = 15;
static constexpr float LASER_BASE_POS_Y = 130;
