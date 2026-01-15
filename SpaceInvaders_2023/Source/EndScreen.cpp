#include "EndScreen.hpp"
#include "StartScreen.hpp"
#include "Game.hpp"
#include <cassert>

EndScreen::EndScreen(Game* game, int s) : GameScene(game), highscore(s) {
	if(_game == nullptr) {
		throw ErrorMessage{ErrorType::NULLPTR_GAME, "EndScreen"};
	}
	enter_new_highscore = _game->GetLeaderboard().CheckNewHighscore(highscore);
	input_char_text = 		TextUI(std::format("INPUT CHARS: 0/{}", MAX_LETTER_COUNT), {600, 600}, HALF_FONT_SIZE);
	name_text = 			TextUI("", getPosition(text_box_bounds) + NAME_POSITION_OFFSET, MAROON);
	cursor_text = 		TextUI("_", getPosition(text_box_bounds) + CURSOR_POSITION_OFFSET, MAROON);
	press_enter_text.position.y = enter_new_highscore ? 800 : 200;
}

void EndScreen::SaveLeaderboard() {
	if(!_game) {
		throw ErrorMessage{ErrorType::SAVE_HIGHSCORE_FAIL, "_game == nullptr"}; //bad but recoverable
	}
	_game->GetLeaderboard().SaveToFile();
}

void EndScreen::Render(Renderer& renderer) {
	if (!enter_new_highscore) {
		renderer.DrawText(press_enter_text);
		_game->GetLeaderboard().Render(renderer);
		return;
	}

	renderer.DrawText(new_highscore_header_text);
	renderer.DrawText(mouse_over_input_box_text);
	DrawRectangleRec(text_box_bounds, LIGHTGRAY);
	DrawRectangleLinesEx(text_box_bounds, 1, mouse_on_text ? RED : DARKGRAY);
	renderer.DrawText(name_text);
	renderer.DrawText(input_char_text);

	if (isValidName()) {
		renderer.DrawText(press_enter_text);
	}
	if (!mouse_on_text) {
		return;
	}
	if (name.size() > MAX_LETTER_COUNT) {
		renderer.DrawText(backspace_text);
		return;
	}
	bool show_cursor = ((frames_counter / CURSOR_FRAMES) % 2) == 0;
	if (show_cursor) {
		renderer.DrawText(cursor_text);
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
	name_text.text = name;
	input_char_text.text = std::format("INPUT CHARS: {}/{}", name.size(), MAX_LETTER_COUNT);
	cursor_text.offset.x = name_text.GetWidth();
}

void EndScreen::EnterNewHighscore() {
	_game->GetLeaderboard().InsertNewHighscore(name, highscore);
	press_enter_text.position.y = 200;
	enter_new_highscore = false;
}

void EndScreen::InitText() {

}

StartScreen* EndScreen::EnterStartScreen() noexcept { return new StartScreen(_game); }
