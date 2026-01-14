#include "EndScreen.hpp"
#include "StartScreen.hpp"
#include "Game.h"
#include <cassert>

EndScreen::EndScreen(Game* game, int s) : GameScene(game), highscore(s) {
	if(_game == nullptr) {
		throw ErrorType::NULLPTR_GAME;
	}
	enterNewHighscore = _game->getLeaderboard().CheckNewHighscore(highscore);
	InitText();
}

void EndScreen::SaveLeaderboard() {
	if(_game) {
		_game->getLeaderboard().SaveToFile();
	}
}

void EndScreen::Render(Renderer& renderer) {
	if (enterNewHighscore) {
		RenderNewHighscore(renderer);
	}
	else {
		ShowScoreboard(renderer);
	}
}

void EndScreen::RenderNewHighscore(Renderer& renderer) {
	renderer.DrawText(newHighscoreHeader);//, DEFAULT_FONT_COLOR);


	renderer.DrawText(mouseOverInputBoxText);
	DrawRectangleRec(textBoxBounds, LIGHTGRAY);
	DrawRectangleLinesEx(textBoxBounds, 2, mouseOnText ? RED : DARKGRAY);
	renderer.DrawText(nameText);
	renderer.DrawText(inputCharText); //Draw the text explaining how many characters are used

	// Explain how to continue when name is input
	if (isValidName()) {
		renderer.DrawText(pressEnterText);
	}

	if (!mouseOnText) {
		return;
	}

	if (name.size() > MAX_LETTER_COUNT) {
		renderer.DrawText(backspaceText);
		return;
	}
	// Draw blinking underscore char
	if (((framesCounter / 20) % 2) == 0) {
		renderer.DrawText("_", getPosition(textBoxBounds) + cursorPositionOffset + Vector2(MeasureText(name.c_str(), DEFAULT_FONT_SIZE), 0));/*, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);*/
	}
}
void EndScreen::ShowScoreboard(Renderer& renderer) {
	// If no highscore or name is entered, show scoreboard and call it a day
	renderer.DrawText(pressEnterText);
	//	renderer.DrawText("PRESS ENTER TO CONTINUE", {600, 200});//, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
	_game->getLeaderboard().Render(renderer);
}

std::optional<GameScene*> EndScreen::Update() {
	if (!enterNewHighscore) {
		if (IsKeyReleased(KEY_ENTER)) {
			return EnterStartScreen();
		}
		return Continue();
	}

	framesCounter++;
	mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBoxBounds);
	SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);

	if (!mouseOnText) {
		framesCounter = 0;
		return Continue();
	}

	GetTypingInput();

	if (isValidName() && IsKeyReleased(KEY_ENTER)) {
		return EnterNewHighscore();
	}
	return Continue();
}

void EndScreen::GetTypingInput() {
	char key = GetCharPressed();
	while (key > 0) {
		if ((key >= ASCII_SPACE) &&
		    (key <= ASCII_RIGHT_BRACKET) &&
		    (name.size() <= MAX_LETTER_COUNT)) {
			name.push_back(key);
			UpdateNameText();
		}
		key = GetCharPressed();  // Check next character in the queue
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) {//Remove chars
		name.pop_back();
		UpdateNameText();
	}
}

void EndScreen::UpdateNameText() {
	nameText.text = name;
	inputCharText.text = std::format("INPUT CHARS: {}/8", name.size());
}

void EndScreen::InitText() {
	pressEnterText = TextUI("PRESS ENTER TO CONTINUE", {600, 800});
	backspaceText = TextUI("Press BACKSPACE to delete chars...", {600, 650}, HALF_FONT_SIZE);
	inputCharText = TextUI("INPUT CHARS: 0/8", {600, 600}, HALF_FONT_SIZE);
	mouseOverInputBoxText = TextUI("PLACE MOUSE OVER INPUT BOX!", {600, 400}, HALF_FONT_SIZE);
	nameText = TextUI("", getPosition(textBoxBounds) + Vector2(5, 8), MAROON);
	newHighscoreHeader = TextUI("NEW HIGHSCORE!", {600, 300}, HEADER_FONT_SIZE);

	pressEnterText.position.y = enterNewHighscore ? 800 : 200;
}

std::nullopt_t EndScreen::EnterNewHighscore() {
	_game->getLeaderboard().InsertNewHighscore(name, highscore);
	pressEnterText.position.y = 200;
	enterNewHighscore = false;
	return std::nullopt;
}


StartScreen* EndScreen::EnterStartScreen() noexcept { return new StartScreen(_game); }
