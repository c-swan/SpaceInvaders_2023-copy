//  Constants.h
//  SpaceInvaders_2023
//  Created by Carl Swanberg on 2025-12-19.

#ifndef Constants_h
#define Constants_h

#include <string>
#include "raylib.h"
using std::string;

/*========    FILE PATHS    ========*/
static constexpr string ASSETS_DIR = "./Assets/";
static constexpr string LEADERBOARD_PATH = "./leaderboard.json";

/*========    WINDOW    ========*/
static constexpr int ORIGINAL_WINDOW_WIDTH = 1920;
static constexpr int ORIGINAL_WINDOW_HEIGHT = 1080;
static constexpr int WINDOW_WIDTH = 1440;	//original: 1920
static constexpr int WINDOW_HEIGHT = 810;	//original: 1080

static constexpr int TARGET_FPS = 60;
static constexpr int NO_ROTATION = 0;

/*========    COLORS    ========*/
static constexpr int ALPHA_OPAQUE = 255;
static constexpr int ALPHA_TRANSPARENT = 0;

static constexpr Color NO_TINT = WHITE;
static constexpr Color BACKGROUND_COLOR = BLACK;
static constexpr Color DEFAULT_FONT_COLOR = YELLOW;
static constexpr Color STAR_COLOR = SKYBLUE;
static constexpr Color TEXTBOX_COLOR = LIGHTGRAY;
static constexpr Color INPUT_ACTIVE_COLOR = RED;
static constexpr Color INPUT_INACTIVE_COLOR = DARKGRAY;
static constexpr Color TEXT_INPUT_COLOR = MAROON;
static constexpr Color WALL_TEXT_COLOR = {167, 42, 33, ALPHA_OPAQUE };

/*========    FONTS    ========*/
static constexpr int TITLE_FONT_SIZE = 120; //160
static constexpr int DEFAULT_FONT_SIZE = 40;
static constexpr int HALF_FONT_SIZE = DEFAULT_FONT_SIZE / 2;
static constexpr int HEADER_FONT_SIZE = 60;

/*========    PROJECTILES    ========*/
static constexpr int PROJECTILE_START_Y = 130;
static constexpr int PROJECTILE_LENGTH = 30;
static constexpr float PROJECTILE_SPEED = 15;
static constexpr int PROJECTILE_BOUNDS = WINDOW_HEIGHT + PROJECTILE_LENGTH;
static constexpr float PROJECTILE_SIZE = 50;

/*========    ALIEN    ========*/
static constexpr int FORMATION_WIDTH = 8;
static constexpr int FORMATION_HEIGHT = 5;
static constexpr int FORMATION_X = 100;
static constexpr int FORMATION_Y = 50;

static constexpr int ALIEN_SPACING = 80;
static constexpr int ALIEN_PADDING_X = 450;
static constexpr int ALIEN_KILL_SCORE = 100;
static constexpr float ALIEN_MOVEMENT_Y = 50; //45?

static constexpr float ALIEN_SPEED = 2;
static constexpr float ALIEN_SIZE = 100;
static constexpr float ALIEN_RADIUS = ALIEN_SIZE / 2;

/*========    STARS    ========*/
static constexpr int STAR_COUNT = 600;
static constexpr float STAR_MAX_SIZE = 2;

static constexpr int BACKGROUND_EDGE_SIZE = 150;
static constexpr int PARALLAX_FACTOR = 15;

/*========    WALL    ========*/
static constexpr int WALL_COUNT = 5;
static constexpr int WALL_MAX_HEALTH = 50;
static constexpr float WALL_SIZE = 200;
static constexpr float WALL_RADIUS = 60;
static constexpr float WALL_BASE_HEIGHT = 250;

/*========    PLAYER    ========*/
static constexpr int PLAYER_MAX_HEALTH = 3;
static constexpr float PLAYER_SPEED = 7;
static constexpr float PLAYER_SIZE = 100;
static constexpr float PLAYER_RADIUS = PLAYER_SIZE / 2;
static constexpr float PLAYER_BASE_HEIGHT = 70;
static constexpr float PLAYER_POS_Y = WINDOW_HEIGHT - PLAYER_BASE_HEIGHT;

static constexpr float SHIP_ANIMATION_TIME = 0.4f;
static constexpr int SHIP_ANIMATION_FRAME_COUNT = 3;

/*========    LEADERBOARD    ========*/
static constexpr int LEFT_MARGIN = 50;
static constexpr int LEADERBOARD_SIZE = 5;
static constexpr int LEADERBOARD_POSITION_X = 50;
static constexpr int LEADERBOARD_POSITION_Y = 100;
static constexpr int LEADERBOARD_SCORE_COLUMN = 300;

static constexpr int ASCII_SPACE = 32;
static constexpr int ASCII_RIGHT_BRACKET = 125;
static constexpr int MAX_LETTER_COUNT = 9;

#endif /* Constants_h */
