#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <print>
#include "Constants.h"
#include "Math.hpp"
#include <cassert>

Game::Game() : textures() {
	_scene = new StartScreen(this);
	SetTargetFPS(TARGET_FPS);               // Set our game to run at 60 frames-per-second
}

void Game::Run() {
	assert(_scene != nullptr);
	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}
}

void Game::Update() {
	if(_scene == nullptr) return;
	if(_scene->_game == nullptr) _scene->_game = this;

	std::optional<GameScene*> status = _scene->Update();
	if(!status.has_value()) return;

	delete _scene;
	_scene = status.value();
	_scene->_game = this;
}

void Game::Render() {
	if(_scene == nullptr) return;
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render();
	EndDrawing();
}
