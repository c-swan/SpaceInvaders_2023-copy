#pragma once
#include "GameScene.hpp"

class StartScreen;

class EndScreen : public GameScene {
public:
	EndScreen(Game* game, int s);
	~EndScreen() { SaveLeaderboard(); }

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	StartScreen* EnterStartScreen() noexcept;

	void RenderNewHighscore(Renderer& renderer);
	void ShowScoreboard(Renderer& renderer);

	void SaveLeaderboard();
	void EnterNewHighscore();
	bool isValidName() const noexcept { return name.size() > 0 && name.size() <= MAX_LETTER_COUNT; }
	bool isKeyValid(char& key) const noexcept { return (key >= ASCII_SPACE) && (key <= ASCII_RIGHT_BRACKET); }
private:
	void InitText();
	void GetTypingInput();
	void UpdateNameText();

	bool enter_new_highscore = false;
	int highscore = 0;

	std::string name = "";

	Rectangle text_box_bounds{ 600, 450, 225, 50 };
	bool mouse_on_text = false;
	int frames_counter = 0;

	TextUI pressEnterText;
	TextUI backspaceText;
	TextUI inputCharText;
	TextUI nameText;
	TextUI mouseOverInputBoxText;
	TextUI newHighscoreHeader;
	TextUI cursorText;

};
