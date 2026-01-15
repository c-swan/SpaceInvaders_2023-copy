#pragma once
#include <raylib.h>

#include <string>
#include <vector>

#include "Constants.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "TexturePack.hpp"
#include "Leaderboard.hpp"

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
