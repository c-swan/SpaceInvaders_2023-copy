#pragma once
#include "GameScene.hpp"
#include "Gameplay.hpp"

class StartScreen : public GameScene {
public:
	StartScreen(Game* game) : GameScene(game) {
		for(auto& t: text) {
			t.CenterAlign();
		}
	}
	~StartScreen() { }

	std::vector<TextUI> text {
		{"SPACE INVADERS", {Window::Width / 2.0f, 100}, TITLE_FONT_SIZE}, //x = 200
		{"PRESS SPACE TO BEGIN", {Window::Width / 2.0f, 350}} //x = 200
	};

	virtual std::optional<GameScene*> Update() {
		if (IsKeyReleased(KEY_SPACE)) {
			return StartGame();
		}
		return Continue();
	}
	virtual void Render(Renderer& renderer) {
		for(auto& t: text) {
			renderer.DrawText(t);
		}
	}
	Gameplay* StartGame() { return new Gameplay(_game); }
};
