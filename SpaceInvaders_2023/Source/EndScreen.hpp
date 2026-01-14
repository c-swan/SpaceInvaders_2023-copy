#pragma once
#include "GameScene.hpp"

class StartScreen;

class EndScreen : public GameScene {
public:
	EndScreen(Game* game, int s);
	~EndScreen() {
		SaveLeaderboard();
	}

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	StartScreen* EnterStartScreen() noexcept;

	void RenderNewHighscore(Renderer& renderer);
	void ShowScoreboard(Renderer& renderer);

	void SaveLeaderboard();
	std::nullopt_t EnterNewHighscore();
	bool isValidName() const noexcept { return name.size() > 0 && name.size() <= MAX_LETTER_COUNT; }
private:
	void InitText();
	void GetTypingInput();
	void UpdateNameText();
	Vector2 getCursorPosition() const noexcept;

	bool enterNewHighscore = false;
	int highscore = 0;

	std::string name = "";

	Rectangle textBoxBounds = { 600, 450, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;

	TextUI pressEnterText;
	TextUI backspaceText;
	TextUI inputCharText;
	TextUI nameText;
	TextUI mouseOverInputBoxText;
	TextUI newHighscoreHeader;
//	Vector2 namePositionOffset = Vector2(5, 8);
	Vector2 cursorPositionOffset = Vector2(8, 12);

};
