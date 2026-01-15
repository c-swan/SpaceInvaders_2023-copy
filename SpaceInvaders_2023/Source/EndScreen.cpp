#include "EndScreen.hpp"
#include "StartScreen.hpp"
#include "game.h"
#include <cassert>

EndScreen::EndScreen(Game* game, int s) : GameScene(game), highscore(s) {
	if(_game == nullptr) {
		throw ErrorMessage{ErrorType::NULLPTR_GAME, "EndScreen"};
	}
	enter_new_highscore = _game->GetLeaderboard().CheckNewHighscore(highscore);
	InitText();
}

void EndScreen::SaveLeaderboard() {
	if(!_game) {
		throw ErrorMessage{ErrorType::SAVE_HIGHSCORE_FAIL, "_game == nullptr"}; //bad but recoverable
	}
	_game->GetLeaderboard().SaveToFile();
}

void EndScreen::Render(Renderer& renderer) {
	if (!enter_new_highscore) {
		renderer.DrawText(pressEnterText);
		_game->GetLeaderboard().Render(renderer);
		return;
	}

	renderer.DrawText(newHighscoreHeader);
	renderer.DrawText(mouseOverInputBoxText);
	DrawRectangleRec(text_box_bounds, LIGHTGRAY);
	DrawRectangleLinesEx(text_box_bounds, 1, mouse_on_text ? RED : DARKGRAY);
	renderer.DrawText(nameText);
	renderer.DrawText(inputCharText);

	if (isValidName()) {
		renderer.DrawText(pressEnterText);
	}

	if (!mouse_on_text) {
		return;
	}
	if (name.size() > MAX_LETTER_COUNT) {
		renderer.DrawText(backspaceText);
		return;
	}
	bool show_cursor = ((frames_counter / CURSOR_FRAMES) % 2) == 0;
	if (show_cursor) {
		renderer.DrawText(cursorText);
	}
}

std::optional<GameScene*> EndScreen::Update() {
	if(!enter_new_highscore) {
		if (IsKeyReleased(KEY_ENTER)) {
			return EnterStartScreen();
		}
		return Continue();
	}

	mouse_on_text = CheckCollisionPointRec(GetMousePosition(), text_box_bounds);
	SetMouseCursor(mouse_on_text ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);

	if (!mouse_on_text) {
		frames_counter = 0;
		return Continue();
	}

	GetTypingInput();
	(++frames_counter) %= (CURSOR_FRAMES * 2);

	if (IsKeyReleased(KEY_ENTER) && isValidName()) {
		EnterNewHighscore();
	}
	return Continue();
}

void EndScreen::GetTypingInput() {
	char key = GetCharPressed();
	while (key > 0) {
		if (isKeyValid(key) && (name.size() <= MAX_LETTER_COUNT)) {
			name.push_back(key);
			UpdateNameText();
		}
		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) {
		name.pop_back();
		UpdateNameText();
	}
}

void EndScreen::UpdateNameText() {
	nameText.text = name;
	inputCharText.text = std::format("INPUT CHARS: {}/{}", name.size(), MAX_LETTER_COUNT);
	cursorText.offset.x = nameText.GetWidth();
}

void EndScreen::EnterNewHighscore() {
	_game->GetLeaderboard().InsertNewHighscore(name, highscore);
	pressEnterText.position.y = 200;
	enter_new_highscore = false;
}

void EndScreen::InitText() {
	pressEnterText = 		TextUI("PRESS ENTER TO CONTINUE", {600, 800});
	backspaceText = 		TextUI("Press BACKSPACE to delete chars...", {600, 650}, HALF_FONT_SIZE);
	inputCharText = 		TextUI(std::format("INPUT CHARS: 0/{}", MAX_LETTER_COUNT), {600, 600}, HALF_FONT_SIZE);
	mouseOverInputBoxText = TextUI("PLACE MOUSE OVER INPUT BOX!", {600, 400}, HALF_FONT_SIZE);
	nameText = 			TextUI("", getPosition(text_box_bounds) + NAME_POSITION_OFFSET, MAROON);
	newHighscoreHeader = 	TextUI("NEW HIGHSCORE!", {600, 300}, HEADER_FONT_SIZE);
	cursorText = 		TextUI("_", getPosition(text_box_bounds) + CURSOR_POSITION_OFFSET, MAROON);
	pressEnterText.position.y = enter_new_highscore ? 800 : 200;
}

StartScreen* EndScreen::EnterStartScreen() noexcept { return new StartScreen(_game); }
