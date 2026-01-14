#pragma once
#include <raylib.h>

#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include "Bunker.h"
#include "Stars.h"

#include <optional>
#include <vector>
#include <string>

#include "Constants.h"
#include "TextUI.h"

class Game;

class GameScene {
public:
	GameScene(Game* game = nullptr) : _game(game) {}
	virtual ~GameScene() {}

	Game* _game = nullptr;
	virtual std::optional<GameScene*> Update() = 0;
	virtual void Render(Renderer& renderer) = 0;
	std::nullopt_t Continue() { return std::nullopt; }
};
