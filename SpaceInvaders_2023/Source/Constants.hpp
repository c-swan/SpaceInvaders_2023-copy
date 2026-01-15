#pragma once
#include <raylib.h> //for Vector2
#include <string>

static constexpr int TARGET_FPS = 60;
static constexpr std::string GAME_TITLE = "SPACE INVADERS";

static constexpr std::string LEADERBOARD_PATH = "./leaderboard.json";
static constexpr std::string ASSETS_DIRECTORY = "./Assets/";

static constexpr int WINDOW_WIDTH = 1920;
static constexpr int WINDOW_HEIGHT = 1080;


static constexpr Vector2 ALIEN_FORMATION_POS = {100, 50};
static constexpr int ALIEN_FORMATION_COLUMNS = 11; //8
static constexpr int ALIEN_FORMATION_ROWS = 5;
static constexpr float ALIEN_SPACING = 80;

static constexpr Color BUNKER_TEXT_COLOR = RED;
static constexpr int BUNKER_COUNT = 5;
static constexpr int BUNKER_MAX_HEALTH = 50;
static constexpr float BUNKER_RADIUS = 60;
static constexpr int BUNKER_POSITION_Y = 250;
static constexpr int BUNKER_SIZE = 200;

static constexpr Color DEFAULT_FONT_COLOR = YELLOW;
static constexpr int TITLE_FONT_SIZE = 160;
static constexpr int HEADER_FONT_SIZE = 60;
static constexpr int DEFAULT_FONT_SIZE = 40;
static constexpr int HALF_FONT_SIZE = DEFAULT_FONT_SIZE / 2;

static constexpr float PLAYER_BASE_HEIGHT = 70;
static constexpr float PLAYER_SPEED = 7;
static constexpr int PLAYER_RADIUS = 50;
static constexpr int PLAYER_MAX_LIVES = 3;
static constexpr int PLAYER_SIZE = 100;

static constexpr int ALIEN_SPEED = 2;
static constexpr float ALIEN_RADIUS = 30;
static constexpr int ALIEN_SIZE = 100;
static constexpr int ALIEN_OFFSET_X = 450;
static constexpr int ALIEN_HIT_SCORE = 100;
static constexpr int ALIEN_SHOOT_TIME = 60;
static constexpr int ALIEN_MOVE_DOWN_DISTANCE = 50;

static constexpr Color STAR_COLOR = SKYBLUE;
static constexpr int STAR_COUNT = 600;
static constexpr int BACKGROUND_EDGE_X = 150;
static constexpr int STAR_SIZE_MIN = 1;
static constexpr int STAR_SIZE_MAX = 4;

static constexpr Color NO_TINT = WHITE;
static constexpr int NO_ROTATION = 0;

static constexpr Color BACKGROUND_COLOR = BLACK;
static constexpr float PROJECTILE_SPEED = 15;
static constexpr float PROJECTILE_HEIGHT = 30;
static constexpr float PROJECTILE_WIDTH = 6;
static constexpr float PLAYER_ANIMATION_FRAME_DURATION = 0.4;
static constexpr float PARALLAX_FACTOR = 15;
static constexpr float PROJECTILE_BASE_POS_Y = 130;

static constexpr std::string ALIEN_TEXTURE_NAME = "Alien";
static constexpr std::string BUNKER_TEXTURE_NAME = "Barrier";
static constexpr std::string PROJECTILE_TEXTURE_NAME = "Laser";
static constexpr std::string SHIP_TEXTURE_NAME = "Ship";
static constexpr int SHIP_TEXTURE_COUNT = 3;

/*========    LEADERBOARD    ========*/
static constexpr int LEFT_MARGIN = 50;
static constexpr Vector2 LEADERBOARD_POSITION {LEFT_MARGIN, 100};
static constexpr int LEADERBOARD_SIZE = 5;
static constexpr int LEADERBOARD_SCORE_COLUMN = 300;

static constexpr int ASCII_SPACE = 32;
static constexpr int ASCII_RIGHT_BRACKET = 125;
static constexpr int MAX_LETTER_COUNT = 8;
static constexpr int CURSOR_FRAMES = 20;
static constexpr Vector2 CURSOR_POSITION_OFFSET = {8, 12};
static constexpr Vector2 NAME_POSITION_OFFSET = {5, 8};
