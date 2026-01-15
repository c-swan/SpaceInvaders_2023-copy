#pragma once
#include <raylib.h>
#include "Constants.h"
#include "TexturePack.hpp"
#include "Window.hpp"
#include <string>
#include <vector>

#include "Leaderboard.hpp"
#include "GameScene.hpp"
#include "StartScreen.hpp"

class Game {
	public:

	Game() : window(), renderer(window), _scene(std::make_unique<StartScreen>(this)) {}
	~Game() = default;

	private:
	Window window;
	Renderer renderer;
	Leaderboard leaderboard;

	std::unique_ptr<GameScene> _scene;

	void Update();
	void Render();

	public:
	void Run();

	Leaderboard& GetLeaderboard() noexcept { return leaderboard; }
	TexturePack texture_pack;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
};
