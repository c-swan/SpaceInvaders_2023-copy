#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Constants.h"
#include <fstream>
#include "Math.h"
#include <algorithm>
#include <ranges>

float Star::offsetX = 0;

void Game::Start() {
	Stars.resize(STAR_COUNT);
	player = Player(&texturePack);

	SpawnWalls();
	SpawnAliens();

	score = 0;
	gameState = State::GAMEPLAY;
}

void Game::SpawnWalls() {
	// creating walls
	float window_width = static_cast<float>(GetScreenWidth());
	float window_height = static_cast<float>(GetScreenHeight());
	float bunker_distance = window_width / (BUNKER_COUNT + 1);
	for (int i = 0; i < BUNKER_COUNT; i++) {
		Bunker bunker(bunker_distance * (i + 1), window_height - BUNKER_POSITION_Y, &texturePack);
		Bunkers.push_back(bunker);
	}
}

void Game::GameOver() {
	Projectiles.clear();
	Bunkers.clear();
	Aliens.clear();
	Stars.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue() {
	SaveLeaderboard();
	gameState = State::STARTSCREEN; //TODO: FSM should use enterState
}

void Game::Launch() {
	gameState = State::STARTSCREEN;
	while (!window.shouldClose()) {	
		Update();
		Render();
	}
}

void Game::Update() {
	switch (gameState) {
	case State::STARTSCREEN:
		StartScreenUpdate(); break;
	case State::GAMEPLAY:
		GameplayUpdate(); break;
	case State::ENDSCREEN:
		EndScreenUpdate(); break;
	default: //SHOULD NOT HAPPEN
		throw std::runtime_error("No game state!"); break;
	}
}

void Game::Render() {
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);

	switch (gameState) {
	case State::STARTSCREEN:
		StartScreenRender(); break;
	case State::GAMEPLAY:
		GameplayRender(); break;
	case State::ENDSCREEN:
		EndScreenRender(); break;
	default: //SHOULD NOT HAPPEN
		throw std::runtime_error("No game state!"); break;
	}
	EndDrawing();
}

void Game::StartScreenUpdate() {
	if (IsKeyReleased(KEY_SPACE)) {
		Start();
	}
}

void Game::StartScreenRender() {
	DrawText("SPACE INVADERS", 200, 100, 160, DEFAULT_FONT_COLOR);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, DEFAULT_FONT_COLOR);
}

void Game::GameplayUpdate() {
	if (IsKeyReleased(KEY_Q)) {
		return GameOver();
	}

	player.Update();
	for (auto& alien : Aliens) {
		alien.Update();

		if (alien.isBehindPlayer()) {
			return GameOver();
		}
	}
	if (player.isDead()) {
		return GameOver();
	}
	if (Aliens.empty()) {
		SpawnAliens();
	}

	UpdateStarPositions();

	for(auto& projectile : Projectiles) {
		projectile.Update();
	}

	if (IsKeyPressed(KEY_SPACE)) {
		MakeProjectile();
	}
	AlienShooting();

	CheckCollisions();
	RemoveInactiveEntities();
}

void Game::CheckCollisions() {
	for(auto& projectile : Projectiles) {
		if (projectile.isActive() && projectile.isPlayerProjectile()) {
			for (auto& alien : Aliens) {
				bool alien_collision = CheckCollision(alien.getCollider(), projectile.getCollider());
//Collider Tests
				DrawRectangleLinesEx(projectile.getCollider(), 5, alien_collision ? GREEN : RED);
				renderer.Render(alien.getCollider(), alien_collision ? GREEN : RED);

				if (alien_collision) {
					projectile.hit();
					alien.hit();
					score += ALIEN_HIT_SCORE;
				}
			}
		}

		//ENEMY PROJECTILES HERE
		for(auto& projectile : Projectiles) {
			if (projectile.isAlienProjectile() && projectile.isActive() && projectile.isWithinPlayerRange()) {
				bool player_collision = CheckCollision(player.getCollider(), projectile.getCollider());

				DrawRectangleLinesEx(projectile.getCollider(), 5, player_collision ? GREEN : RED);
				renderer.Render(player.getCollider(), player_collision ? GREEN : RED);

				if (player_collision) {
					projectile.hit();
					player.hit();
				}
			}
		}

		for (auto& bunker : Bunkers) {
			if(projectile.isActive() && (projectile.getPosition().y > bunker.getPosition().y - bunker.getRadius()) && (projectile.getPosition().y < bunker.getPosition().y + bunker.getRadius())) {
				bool bunker_collision = CheckCollisionCircleRec(bunker.getPosition(), bunker.getRadius(), projectile.getCollider());
				DrawRectangleLinesEx(projectile.getCollider(), 5, bunker_collision ? GREEN : RED);
				renderer.Render(bunker.getCollider(), bunker_collision ? GREEN : RED);

				if (bunker_collision) {
					projectile.hit();
					bunker.hit();
				}
			}
		}
	}
}



void Game::MakeProjectile() {
	Projectiles.push_back(Projectile(
						   Projectile::Type::Player,
						   {
							   player.getX(),
							   GetScreenHeight() - LASER_BASE_POS_Y
						   },
						   &texturePack)
				    );
}

void Game::AlienShooting() {
	if (Aliens.empty()) {
		return;
	}
	alienShootTimer++;
	if (alienShootTimer < 60) {
		return;
	}

	int randomAlienIndex = rand() % Aliens.size(); //don't forget to seed

	Projectiles.push_back(Projectile(
						   Projectile::Type::Alien,
						   Aliens[randomAlienIndex].position,
						   &texturePack
						   )
				    );
	alienShootTimer = 0;
}

void Game::RemoveInactiveEntities() {

	std::erase_if(Projectiles, [](auto& projectile) { return !projectile.isActive() || projectile.isOutOfBounds(); });
	std::erase_if(Aliens, [](auto& alien) { return alien.isDead(); });
	std::erase_if(Bunkers, [](auto& bunker) { return bunker.isDead(); });
}
//
//	for (int i = 0; i < Projectiles.size(); i++) {
//		if (!Projectiles[i].active) {
//			Projectiles.erase(Projectiles.begin() + i);
//			// Prevent the loop from skipping an instance because of index changes, since all insances after
//			// the killed objects are moved down in index. This is the same for all loops with similar function
//			i--;
//		}
//	}
//	for (int i = 0; i < Aliens.size(); i++) {
//		if (!Aliens[i].active) {
//			Aliens.erase(Aliens.begin() + i);
//			i--;
//		}
//	}
//	for (int i = 0; i < Bunkers.size(); i++) {
//		if (!Bunkers[i].active) {
//			Bunkers.erase(Bunkers.begin() + i);
//			i--;
//		}
//	}
//}

void Game::GameplayRender() {
	for(auto& star : Stars) {
		star.Render(renderer);
	}
	renderer.DrawText(TextFormat("Score: %i", score), {50, 20});
	renderer.DrawText(TextFormat("Lives: %i", player.lives), {50, 70});
	player.Render(renderer);
	for(auto& bunker: Bunkers) {
		bunker.Render(renderer);
	}
	for (auto& alien : Aliens) {
		alien.Render(renderer);
	}
	for(auto& projectile : Projectiles) {
		projectile.Render(renderer);
	}
}

void Game::EndScreenUpdate() {
	if (IsKeyReleased(KEY_ENTER) && !newHighScore) {
		return Continue();
	}

	if (newHighScore) {
		mouseOnText = (CheckCollisionPointRec(GetMousePosition(), textBox));
		SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
		if (mouseOnText) {


			// Get char pressed on the queue
			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0) {
				// NOTE: Only allow keys in range [32..125]
				if ((key >= 32) && (key <= 125) && (letterCount < 9)) {
					name[letterCount] = static_cast<char>(key);
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}
				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) {
					letterCount = 0;
				}
				name[letterCount] = '\0';
			}
		}

		framesCounter = mouseOnText ? framesCounter + 1 : 0;

		// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add
		// name + score to scoreboard
		if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER)) {
			std::string nameEntry(name);
			InsertNewHighScore(std::string(name));
			newHighScore = false;
		}
	}
}

struct TextUI {
	TextUI(std::string txt) : text(txt) {}
	TextUI(std::string txt, Vector2 pos) : text(txt), position(pos) {}
	TextUI(std::string txt, Vector2 pos, int size = DEFAULT_FONT_SIZE, Color c = DEFAULT_FONT_COLOR) : text(txt), position(pos), fontSize(size), fontColor(c) {}

	std::string text = "";
	Vector2 position = {0,0};
	int fontSize = DEFAULT_FONT_SIZE;
	Color fontColor = DEFAULT_FONT_COLOR;
	void Render() {DrawText(text.c_str(), position.x, position.y, fontSize, fontColor);}
};

void Game::EndScreenRender() {
	if (newHighScore) {
		std::vector<TextUI> Texts;
		for(auto& text : Texts) {
			text.Render();
		}
		TextUI highscoreText("NEW HIGHSCORE!", {600, 300}, TITLE_FONT_SIZE);
		highscoreText.Render();
		DrawText("NEW HIGHSCORE!", 600, 300, TITLE_FONT_SIZE, DEFAULT_FONT_COLOR);

		// BELOW CODE IS FOR NAME INPUT RENDER
		DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, HALF_FONT_SIZE, DEFAULT_FONT_COLOR);

		DrawRectangleRec(textBox, LIGHTGRAY);
		DrawRectangleLinesEx(textBox, 5, mouseOnText ? RED : DARKGRAY);


		//Draw the name being typed out
		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, DEFAULT_FONT_SIZE, MAROON);

		//Draw the text explaining how many characters are used
		DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, DEFAULT_FONT_COLOR);

		if (mouseOnText) {
			if (letterCount < 9) {
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0) {
					DrawText("_", (int)textBox.x + 8 + MeasureText(name, DEFAULT_FONT_SIZE), (int)textBox.y + 12, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
				}
			}
			else {
				//Name needs to be shorter
				DrawText("Press BACKSPACE to delete chars...", 600, 650, HALF_FONT_SIZE, DEFAULT_FONT_COLOR);
			}
		}

		// Explain how to continue when name is input
		if (letterCount > 0 && letterCount < 9) {
			DrawText("PRESS ENTER TO CONTINUE", 600, 800, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
		}
	}
	else {
		// If no highscore or name is entered, show scoreboard and call it a day
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
		DrawText("LEADERBOARD", 50, 100, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);

		for (int i = 0; i < Leaderboard.size(); i++) {
			char* tempNameDisplay = Leaderboard[i].name.data();
			DrawText(tempNameDisplay, 50, 140 + (i * DEFAULT_FONT_SIZE), DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
			DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * DEFAULT_FONT_SIZE), DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
		}
	}
}

//====

void Game::SpawnAliens() {
	for (int row = 0; row < ALIEN_FORMATION_HEIGHT; row++) {
		for (int col = 0; col < ALIEN_FORMATION_WIDTH; col++) {
			Alien newAlien = Alien(ALIEN_FORMATION_POS.x + ALIEN_OFFSET_X + (col * ALIEN_SPACING),
						     ALIEN_FORMATION_POS.y + (row * ALIEN_SPACING),
						     &texturePack);
			Aliens.push_back(newAlien);
		}
	}
}
void Game::InsertNewHighScore(std::string name) {
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++) {
		if (newData.score > Leaderboard[i].score) //find correct place to insert and then remove last element
		{ //maybe insert then sort? or use algorithm to find position
			Leaderboard.insert(Leaderboard.begin() + i, newData);
			Leaderboard.pop_back();

			return;
		}
	}
}

void Game::LoadLeaderboard() {
	//TODO: well this explains why I don't seem to be able to see anything?
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::SaveLeaderboard()
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::ofstream file; //changed to ofstream to create file if does not exist

	file.open("./Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}
