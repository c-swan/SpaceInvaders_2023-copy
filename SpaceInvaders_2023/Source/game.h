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
#include "StartScreen.hpp"

class Game {
	public:

	Game() : window(), renderer(window) {
		SetTargetFPS(FPS);
		_scene = std::make_unique<StartScreen>(this);
	}
	~Game() {}


	private:
	Window window;
	Renderer renderer;
	Leaderboard leaderboard;

	std::unique_ptr<GameScene> _scene;

	void Update();
	void Render();

	public:
	void Run();

	Leaderboard& getLeaderboard() noexcept { return leaderboard; }

	TexturePack texturePack;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
};
