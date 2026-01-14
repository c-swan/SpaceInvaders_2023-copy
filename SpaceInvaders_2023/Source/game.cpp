#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Constants.h"
#include <fstream>
#include "Math.h"
#include <algorithm>
#include <ranges>


#include <cassert>
#include <exception>

void Game::Run() {
	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}
}

void Game::Update() {
	if(_scene == nullptr) {
		throw std::runtime_error("_scene == nullptr");
	}
	std::optional<GameScene*> status = _scene->Update();
	if(!status.has_value()) return;

	_scene.reset(status.value());
	_scene->_game = this; //just to be extra sure...
}

void Game::Render() {
	if(_scene == nullptr) {
		throw std::runtime_error("_scene == nullptr");
	}
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render(renderer);
	EndDrawing();
}
