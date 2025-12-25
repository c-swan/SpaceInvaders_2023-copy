//
//  Constants.h
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef Constants_h
#define Constants_h

#include <string>
#include "raylib.h"

static constexpr std::string ASSETS_DIR = "./Assets/";

static constexpr int ORIGINAL_WINDOW_WIDTH = 1920;
static constexpr int ORIGINAL_WINDOW_HEIGHT = 1080;
static constexpr int WINDOW_WIDTH = 1440;	//original: 1920
static constexpr int WINDOW_HEIGHT = 810;	//original: 1080

static constexpr float RESOLUTION_SCALE = WINDOW_WIDTH / ORIGINAL_WINDOW_WIDTH; //0.75
static constexpr int TARGET_FPS = 60;
//MacBook air resolution.... 1470 x 956

// for later, make a file where you can adjust the number of walls (config file)
static constexpr int WALL_COUNT = 5;
static constexpr int PLAYER_BASE_HEIGHT = 70;
static constexpr int PROJECTILE_START_Y = 130;


static constexpr int ALIEN_SPEED = 2;
static constexpr int PLAYER_SPEED = 7;
static constexpr int PROJECTILE_SPEED = 15;
static constexpr int PROJECTILE_BOUNDS = WINDOW_HEIGHT + 420 * RESOLUTION_SCALE;
static constexpr float SHIP_ANIMATION_TIME = 0.4f;

static constexpr int PROJECTILE_LENGTH = 30;

static constexpr int MAX_LIVES = 3;
static constexpr int PARALLAX_FACTOR = 15;

static constexpr int ALIEN_PLAYER_TEXTURE_RESOLUTION = 352;
static constexpr int WALL_TEXTURE_RESOLUTION = 704;
static constexpr int PROJECTILE_TEXTURE_RESOLUTION = 176;

static constexpr int ALIEN_KILL_SCORE = 100;

static constexpr int ASCII_SPACE = 32;
static constexpr int ASCII_RIGHT_BRACKET = 125;
static constexpr int MAX_LETTER_COUNT = 9;

static constexpr int ALPHA_OPAQUE = 255;
static constexpr int ALPHA_TRANSPARENT = 0;
static constexpr Color STAR_COLOR = SKYBLUE;

static constexpr int NO_ROTATION = 0;
static constexpr Color NO_TINT = WHITE;
static constexpr Color TEXT_COLOR = YELLOW;
static constexpr Color TEXTBOX_COLOR = LIGHTGRAY;
static constexpr Color INPUT_ACTIVE_COLOR = RED;
static constexpr Color WALL_TEXT_COLOR = Color{167, 42, 33, ALPHA_OPAQUE };
static constexpr Color INPUT_INACTIVE_COLOR = DARKGRAY;
static constexpr Color TEXT_INPUT_COLOR = MAROON;

static constexpr int TITLE_FONT_SIZE = 120; //160
static constexpr int DEFAULT_FONT_SIZE = 40;
static constexpr int HALF_FONT_SIZE = DEFAULT_FONT_SIZE / 2;
static constexpr int HEADER_FONT_SIZE = 60;

static constexpr int FORMATION_WIDTH = 8;
static constexpr int FORMATION_HEIGHT = 5;
static constexpr int ALIEN_SPACING = 80;
static constexpr int FORMATION_X = 100;
static constexpr int FORMATION_Y = 50;
static constexpr int ALIEN_PADDING_X = 450;
static constexpr int ALIEN_HEIGHT = 187;
static constexpr float ALIEN_MOVEMENT_Y = 50; //45?

static constexpr int STAR_COUNT = 600;

static constexpr int WALL_RADIUS = 60; //60
static constexpr int WALL_BASE_HEIGHT = 250; //250
static constexpr int WALL_MAX_HEALTH = 50;
static constexpr int WALL_SIZE = 200;


static constexpr int BACKGROUND_EDGE_SIZE = 150;
static constexpr int STAR_MAX_SIZE = 2;
static constexpr int ALIEN_RADIUS = 50;
static constexpr int ALIEN_SIZE = 100;

static constexpr int PROJECTILE_SIZE = 50;
static constexpr int PLAYER_SIZE = 100;
static constexpr int PLAYER_RADIUS = 50;


static constexpr int LEADERBOARD_SIZE = 5;
static constexpr int LEADERBOARD_LAST = LEADERBOARD_SIZE - 1;


#endif /* Constants_h */
