#pragma once
//#include "raylib.h"
#include "Window.hpp"
#include "Leaderboard.hpp"
#include "TextureAtlas.hpp"
#include "Sounds.hpp"
#include <string>
#include <vector>

#include "Constants.h"
#include "Math.hpp"
#include "GameScene.hpp"

//#include "Entities.hpp"

class Game {
	public:
	Game() : window(), textureAtlas(), sounds(), leaderboard() { SetTargetFPS(TARGET_FPS); _scene = std::make_unique<StartScreen>(this); }
	~Game() { } //uniqe_ptr self delete

	void Run();
	void Update();
	void Render();
	void Render(const Sprite& sprite);

	Leaderboard& getLeaderboard() noexcept { return leaderboard; }
	TextureAtlas& getTextureAtlas() noexcept { return textureAtlas; }
	Sounds& getSounds() noexcept { return sounds; }
	Texture2D& getTexture(TextureAtlas::Textures textureName) { return textureAtlas.getTexture(textureName); }
	vector<Texture2D*> getShipTextures() {
		return vector {
			&getTexture(TextureAtlas::Textures::SHIP1),
			&getTexture(TextureAtlas::Textures::SHIP2),
			&getTexture(TextureAtlas::Textures::SHIP3)
		};
	}
private:
	Window window;
	TextureAtlas textureAtlas;
	Sounds sounds;
	Leaderboard leaderboard;
	
	std::unique_ptr<GameScene> _scene;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
};
