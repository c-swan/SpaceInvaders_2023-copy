//
//  Constants.h
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef Constants_h
#define Constants_h

#include <string>

static constexpr std::string ASSETS_DIR = "./Assets/";

static constexpr int SCREEN_WIDTH = 1200;	//original: 1920
static constexpr int SCREEN_HEIGHT = 717;	//original: 1080
//MacBook air resolution.... 1470 x 956

// for later, make a file where you can adjust the number of walls (config file)
static constexpr int WALL_COUNT = 5;
static constexpr int PLAYER_BASE_HEIGHT = 70;

static constexpr int ALIEN_SPEED = 2;
static constexpr int PLAYER_SPEED = 2;
static constexpr int PROJECTILE_SPEED = 15;

static constexpr int STAR_AMOUNT = 600;

static constexpr int LEADERBOARD_SIZE = 5;
static constexpr int LEADERBOARD_LAST = LEADERBOARD_SIZE - 1;


#endif /* Constants_h */
