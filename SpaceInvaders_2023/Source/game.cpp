#include "game.h"
//#include <iostream>
//#include <vector>
//#include <chrono>
//#include <thread>
//#include <fstream>
//#include <print>
#include "Constants.h"
//#include "Math.hpp"
#include <cassert>

void Game::Run() {
	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}
}

void Game::Update() {
	if(_scene == nullptr) return;
	//assert(_scene != nullptr);// != nullptr);
	//assert(_scene->_game != nullptr);// != nullptr);

	std::optional<GameScene*> status = _scene->Update();
	if(!status.has_value()) return;

//	delete _scene;
	_scene.reset(status.value());
	_scene->_game = this;
}

void Game::Render() {
//	assert(_scene != nullptr);
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render();
	EndDrawing();
}
