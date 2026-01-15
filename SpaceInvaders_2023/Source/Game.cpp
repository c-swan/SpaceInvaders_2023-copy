#include "Game.hpp"
#include "ErrorHandling.hpp"

int Window::Width = WINDOW_WIDTH;
int Window::Height = WINDOW_HEIGHT;

void Game::Run() {
	while (!window.shouldClose()) {
		if(!_scene) {
			throw ErrorType::NULLPTR_SCENE;
		}
		Update();
		Render();
	}
}
void Game::Update() {
	std::optional<GameScene*> status = _scene->Update();
	if(status.has_value()) {
		_scene.reset(status.value());
		_scene->_game = this; //just to be extra sure...
	}
}
void Game::Render() {
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);
	_scene->Render(renderer);
	EndDrawing();
}
