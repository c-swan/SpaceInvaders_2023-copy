//
//  GameState.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#include "GameScene.hpp"
#include "EndScreen.hpp"
#include "StartScreen.hpp"
#include "Gameplay.hpp"

#include "game.h"
#include "Math.h"
#include <raylib.h>
#include "Constants.h"
#include <optional>
#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "Renderer.h"
#include "Bunker.h"
#include "Window.hpp"

//static vars
float Star::offset_x = 0;
Vector2 Alien::swarm_position = {0,0};
int Window::Width = WINDOW_WIDTH;
int Window::Height = WINDOW_HEIGHT;

//std::optional<GameScene*> StartScreen::Update() {
//	if (IsKeyReleased(KEY_SPACE)) {
//		return StartGame();
//	}
//	return Continue();
//}

