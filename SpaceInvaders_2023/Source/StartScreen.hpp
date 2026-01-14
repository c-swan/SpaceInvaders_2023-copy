#pragma once
#include "GameScene.hpp"
#include "Gameplay.hpp"

class StartScreen : public GameScene {
public:
	StartScreen(Game* game) : GameScene(game) { }
	~StartScreen() { }

	std::vector<TextUI> text {
		{"SPACE INVADERS", {200, 100}, TITLE_FONT_SIZE},
		{"PRESS SPACE TO BEGIN", {200, 350}}
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
