#include "game.h"
#include "Constants.h"
#include <cassert>

void Game::Run() {
	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}
}

void Game::Update() {
	assert(_scene != nullptr);

	std::optional<GameScene*> status = _scene->Update();
	if(!status.has_value()) return;

	_scene.reset(status.value());
	_scene->_game = this;
}

void Game::Render() {
	assert(_scene != nullptr);
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render();
	EndDrawing();
}
