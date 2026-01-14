#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Assets.h"
#include "Window.hpp"
#include <string>
#include <vector>
#include <print>

#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include "Bunker.h"
#include "Stars.h"
#include "Leaderboard.hpp"
#include "GameScene.hpp"

class Game {
	public:
	
	Game() : window(), renderer(window) {
		SetTargetFPS(FPS);
		_scene = std::make_unique<StartScreen>(this);
	}
	~Game() {}

	Window window;
	Renderer renderer;
	TexturePack texturePack;

	std::unique_ptr<GameScene> _scene;

	void Run();
	void Update();
	void Render();

	Leaderboard leaderboard;
	Leaderboard& getLeaderboard() noexcept { return leaderboard; }

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
};
