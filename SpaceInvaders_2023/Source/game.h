#pragma once
#include "raylib.h"
#include <vector>
#include "Textures.hpp"
#include "Sounds.hpp"
#include <string>
#include "Constants.h"
#include "Math.hpp"
#include "Window.hpp"
#include "Sounds.hpp"
#include "GameScene.hpp"
#include "Leaderboard.hpp"
#include "Entities.hpp"

class Game {
	public:
	Game();
	~Game() { if(_scene) delete _scene; }

	void Run();
	void Update();
	void Render();
	void Render(const Sprite& sprite);

	Leaderboard& getLeaderboard() noexcept { return leaderboard; }
	Textures& getTextures() noexcept { return textures; }
	Sounds& getSounds() noexcept {return sounds; }

private:
	Window window;
	Textures textures;
	Sounds sounds;
	Leaderboard leaderboard;
	
	GameScene* _scene = nullptr;
};
