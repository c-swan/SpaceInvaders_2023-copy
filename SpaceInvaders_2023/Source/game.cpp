#include "game.h"
#include "ErrorHandling.h"
#include <cassert>
#include <exception>

int Window::Width = WINDOW_WIDTH;
int Window::Height = WINDOW_HEIGHT;

void Game::Run() {
	while (!window.shouldClose()) { //Detect window close button or ESC key
		if(_scene == nullptr) {  //"_scene == nullptr"
			throw ErrorType::NULLPTR_SCENE;
		}
		Update();
		Render();
	}
}

void Game::Update() {
	std::optional<GameScene*> status = _scene->Update();
	if(!status.has_value()) {
		return;
	}

	_scene.reset(status.value());
	_scene->_game = this; //just to be extra sure...
}
void Game::Render() {
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render(renderer);
	EndDrawing();
}
