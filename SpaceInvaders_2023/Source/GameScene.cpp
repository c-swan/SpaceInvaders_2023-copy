//
//  GameScene.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//
#include "GameScene.hpp"
#include "raylib.h"
#include "Constants.h"
#include "Render.h"
#include <optional>
#include <print>
#include <string>
#include <vector>
#include "Entities.hpp"
#include "game.h"
#include <algorithm>
#include <cassert>

using namespace Render;
using Textures = TextureAtlas::Textures;

//float Star::star_offset_x = 0;

std::optional<GameScene*> StartScreen::Update() {
	if (IsKeyReleased(KEY_SPACE)) {
		return StartGame();
	}
	return {};
}

void StartScreen::Render() {
	Render::DrawTextCentered("SPACE INVADERS", {WINDOW_WIDTH / 2, 100}, TITLE_FONT_SIZE); //x:200, y:100
	Render::DrawTextCentered("PRESS SPACE TO BEGIN", {WINDOW_WIDTH / 2, 350}); //200,350
}


Gameplay::Gameplay(Game* game) : GameScene(game), player(game->getShipTextures()) {
	assert(_game != nullptr);
	if(_game == nullptr) return;

	Stars.resize(STAR_COUNT);

	for (int i = 0; i < WALL_COUNT; i++)  {
		Wall newWall(i, &_game->getTexture(Textures::BARRIER));
		Walls.push_back(newWall);
	}
}

Gameplay::~Gameplay() {
	Stars.clear();
	PlayerProjectiles.clear(); //GameplayScene Destructor
	EnemyProjectiles.clear(); //GameplayScene Destructor
	Walls.clear();
	Aliens.clear();
}

std::optional<GameScene*> Gameplay::Update() {
	if (IsKeyReleased(KEY_Q)) {
		return GameOver();
	}
	if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_PAUSE) || IsKeyReleased(KEY_P)) {
		Pause(); return {};
	}
	if(paused) {
		return {};
	}

	SpawnAliens();

	//MAKE PROJECTILE (inputs first)
	if (IsKeyPressed(KEY_SPACE)) {
		PlayerProjectile newPlayerProjectile(&_game->getTexture(Textures::LASER), player.getX());
		PlayerProjectiles.push_back(newPlayerProjectile);
	}

	player.Update();

	for(auto &alien : Aliens) {
		alien.Update();
	}
	if(std::ranges::any_of( Aliens, [](Alien& alien) { return alien.getY() > PLAYER_POS_Y; } )) { return GameOver(); }

	for(auto &projectile : PlayerProjectiles) {
		projectile.Update();
	}
	for(auto &projectile : EnemyProjectiles) {
		projectile.Update();
	}

	Star::star_offset_x = -player.getX() / PARALLAX_FACTOR;

	CheckAllCollisions();

	if (player.isDead()) return GameOver();

	AliensShooting();
	CleanUpEntities();
	return {};
}

EndScreen* Gameplay::GameOver() noexcept {
	return new EndScreen(_game, score);
}

void Gameplay::Render() {
	for(auto &star : Stars) {
		star.Render();
	}
	Render(player);
	for (auto &wall : Walls) {
		Render(wall);
	}
	for (auto &alien : Aliens) {
		Render(alien);
	}
	for(auto &projectile : PlayerProjectiles) {
		Render(projectile);
	}
	for(auto &projectile : EnemyProjectiles) {
		Render(projectile);
	}

	Render::DrawTextCounter("Score", score, {LEFT_MARGIN, 20});
	Render::DrawTextCounter("Lives", player.getHealth(), {LEFT_MARGIN, 70});

	if(paused) Render::DrawTextCentered("PAUSED", {WINDOW_WIDTH / 2, WINDOW_WIDTH / 2}, HEADER_FONT_SIZE);
}

void Gameplay::CheckAllCollisions() {
	for(auto &projectile : PlayerProjectiles) {
		for(auto &alien : Aliens) {
			if (CheckCollision(alien.getCollider(), projectile.getCollider())) {
				projectile.Hit();
				alien.Hit();
				score += ALIEN_KILL_SCORE;
			}
		}
		for(auto &wall : Walls) {
			if (CheckCollision(wall.getCollider(), projectile.getCollider())) {
				projectile.Hit();
				wall.Hit();
			}
		}
	}

	for(auto &projectile : EnemyProjectiles) {
		if (CheckCollision(player.getCollider(), projectile.getCollider())) {
			_game->getSounds().playHitSound();
			projectile.Hit();
			player.Hit();
			if(player.isDead()) return;
		}

		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
		for(auto &wall : Walls) {
			if (CheckCollision(wall.getCollider(), projectile.getCollider())) {
				projectile.Hit();
				wall.Hit();
			}
		}
	}
}

EndScreen::EndScreen(Game* game, int s) : GameScene(game), score(s) {
	assert(_game);
	newHighScore = _game->getLeaderboard().CheckNewHighscore(score);
}

EndScreen::~EndScreen() {
	assert(_game);
	_game->getLeaderboard().SaveToFile();
}
void EndScreen::ShowScoreboard() {
	Render::DrawTextCentered("PRESS ENTER TO CONTINUE", {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200});
	if(_game == nullptr) return;
	_game->getLeaderboard().Render();
}

void EndScreen::DrawInputBox() {
	DrawRectangleRec(textBoxBounds, TEXTBOX_COLOR);

	Color inputFieldColor = (mouseOnText ? INPUT_ACTIVE_COLOR : INPUT_INACTIVE_COLOR);
	Render::DrawRectangleLines(textBoxBounds, inputFieldColor);

	//Draw the name being typed out
	DrawText(name, textBoxBounds + Vector2(5, 8), DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);

	Render::DrawText(std::format("INPUT CHARS: {}/{}", letterCount, MAX_LETTER_COUNT - 1), Vector2{WINDOW_WIDTH / 2, 600}, HALF_FONT_SIZE);

	if (!mouseOnText) return;

	if (letterCount < MAX_LETTER_COUNT) { return DrawInputCursor(); }

	Render::DrawTextCentered("Press BACKSPACE to delete chars...", {WINDOW_WIDTH / 2, 650}, HALF_FONT_SIZE);
}

void EndScreen::DrawInputCursor() {
	if (((framesCounter / 20) % 2) != 0) return;
	//DrawTextCentered("_", textBoxBounds, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);
	DrawText("_", textBoxBounds + Vector2(MeasureText(name, DEFAULT_FONT_SIZE) + 8, 12), DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);
}
void EndScreen::Render() {
	if (!newHighScore) return ShowScoreboard();

	Render::DrawTextCentered("NEW HIGHSCORE!", {WINDOW_WIDTH / 2, 300}, HEADER_FONT_SIZE); //y-pos = 300 down from
	Render::DrawTextCentered("PLACE MOUSE OVER INPUT BOX!", {WINDOW_WIDTH / 2, 400}, HALF_FONT_SIZE);

	DrawInputBox();

	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT) { // Explain how to continue when name is input
		Render::DrawTextCentered("PRESS ENTER TO CONTINUE", {WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100}); //600, 800
	}
}

std::optional<GameScene*> EndScreen::Update() {
	if (IsKeyReleased(KEY_ENTER) && !newHighScore) { //Exit endscreen
		return new StartScreen(_game);
	}

	if (newHighScore) {
		mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBoxBounds);

		SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
		if (mouseOnText) {

			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0)
			{
				// NOTE: Only allow keys in range [32..125] //why not 126: '~' ?
				if ((key >= ASCII_SPACE) && (key <= ASCII_RIGHT_BRACKET) && (letterCount < MAX_LETTER_COUNT))
				{
					name[letterCount] = static_cast<char>(key);
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
			framesCounter++;
		}
		else {
			framesCounter = 0;
		}

		// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add
		// name + score to scoreboard
		if (letterCount > 0 && letterCount < MAX_LETTER_COUNT && IsKeyReleased(KEY_ENTER)) {
			std::string nameEntry(name);
			if(_game) _game->getLeaderboard().InsertNewHighscore(nameEntry, score);
			newHighScore = false; //new high score was entered, high score updated
		}
	}
	return {};
}

void Gameplay::CleanUpEntities() {
	std::erase_if(EnemyProjectiles, [](const EnemyProjectile& projectile) { return projectile.isHidden(); });
	std::erase_if(PlayerProjectiles, [](const PlayerProjectile& projectile) { return projectile.isHidden(); });
	std::erase_if(Aliens, [](const Alien& alien) { return alien.isHidden(); });
	std::erase_if(Walls, [](const Wall& wall) { return wall.isHidden(); });
	//REMOVE INACTIVE/DEAD SPRITE ENTITIES
	//	for (int i = 0; i < EnemyProjectiles.size(); i++) {
	//		if (EnemyProjectiles[i].isHidden()) {
	//			EnemyProjectiles.erase(EnemyProjectiles.begin() + i);
	//			// Prevent the loop from skipping an instance because of index changes, since all insances after
	//			// the killed objects are moved down in index. This is the same for all loops with similar function
	//			i--;
	//		}
	//	}
	//
	//	for (int i = 0; i < PlayerProjectiles.size(); i++) {
	//		//			if (Projectiles[i].active == false)
	//		if (PlayerProjectiles[i].isHidden()) {
	//			PlayerProjectiles.erase(PlayerProjectiles.begin() + i);
	//			// Prevent the loop from skipping an instance because of index changes, since all insances after
	//			// the killed objects are moved down in index. This is the same for all loops with similar function
	//			i--;
	//		}
	//	}
	//	for (int i = 0; i < Aliens.size(); i++) {
	//		if (Aliens[i].isHidden()) {
	//			Aliens.erase(Aliens.begin() + i);
	//			i--;
	//		}
	//	}
	//
	//	for (int i = 0; i < Walls.size(); i++) {
	//		if (Walls[i].isHidden()) {
	//			Walls.erase(Walls.begin() + i);
	//			i--;
	//		}
	//	}
}

void Gameplay::SpawnAliens() {
	if(!Aliens.empty() || _game == nullptr) return;
	for (int row = 0; row < FORMATION_HEIGHT; row++) {
		for (int col = 0; col < FORMATION_WIDTH; col++) {
			Aliens.push_back(Alien(col, row, &_game->getTexture(Textures::ALIEN)));
		}
	}
}

void Gameplay::AliensShooting() {
	if (Aliens.empty()) return;

	shootTimer++;
	if (shootTimer < TARGET_FPS ) return; //once per second

	int random_i = rand() % Aliens.size();
	EnemyProjectile newEnemyProjectile(&_game->getTexture(Textures::LASER), Aliens[random_i].getPosition());
	EnemyProjectiles.push_back(newEnemyProjectile);
	shootTimer = 0;
}
