//
//  GameState.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#include "GameScene.hpp"
#include "game.h"
#include "Math.h"
#include <raylib.h>
#include "Constants.h"
#include <optional>
#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "Renderer.h"
#include "Bunker.h"

float Star::offsetX = 0;
Vector2 Alien::swarmPosition = {0,0};

std::optional<GameScene*> StartScreen::Update() {
	if (IsKeyReleased(KEY_SPACE)) {
		return StartGame();
	}
	return std::nullopt;
}

void StartScreen::Render(Renderer& renderer) {
	for(auto& t: text) {
		renderer.DrawText(t);
	}
}


Gameplay::Gameplay(Game* game) : GameScene(game), player(&game->texturePack), alienSwarm(ALIEN_FORMATION_ROWS, ALIEN_FORMATION_COLUMNS, &game->texturePack), scoreText("Score: 0", {50, 20}), livesText(std::format("Lives: {}", player.lives), {50, 70}) {
	if(_game == nullptr) { throw std::invalid_argument("_game == nullptr"); }

	Stars.resize(STAR_COUNT);
	SpawnAliens();
	SpawnBunkers();

}

void Gameplay::SpawnBunkers() {
	float bunker_pos_y = GetScreenHeight() - BUNKER_POSITION_Y;
	float bunker_distance = GetScreenWidth() / (BUNKER_COUNT + 1);
	for (int i = 0; i < BUNKER_COUNT; i++) {
		Bunkers.emplace_back( Bunker(bunker_distance * (i + 1), bunker_pos_y, &_game->texturePack) );
	}
}
//
//Gameplay::~Gameplay() {
//	Stars.clear();
//	Projectiles.clear(); //GameplayScene Destructor
//	Aliens.clear(); //GameplayScene Destructor
//	Bunkers.clear();
//}

EndScreen* Gameplay::GameOver() noexcept { return new EndScreen(_game, score); }

std::optional<GameScene*> Gameplay::Update() {
	if (IsKeyReleased(KEY_Q)) {
		return GameOver();
	}

	player.Update();
	alienSwarm.Update();
	if(alienSwarm.isBehindPlayer()) {
		return GameOver();
	}
//	for (auto& alien : Aliens) {
//		alien.Update();
//
//		if (alien.isBehindPlayer()) {
//			return GameOver();
//		}
//	}
	if (player.isDead()) {
		return GameOver();
	}
	if (alienSwarm.empty()) {
		SpawnAliens();
	}

	UpdateStarPositions();

	for(auto& projectile : Projectiles) {
		projectile.Update();
	}

	if (IsKeyPressed(KEY_SPACE)) {
		MakeProjectile();
	}
	AliensShooting();

	CheckAllCollisions();
	RemoveInactiveEntities();
	return std::nullopt;
}

void Gameplay::MakeProjectile() {
	Projectiles.emplace_back(Projectile(
							Projectile::Type::Player,
							{ player.getX(), GetScreenHeight() - PROJECTILE_BASE_POS_Y },
							&_game->texturePack)
					 );
}


void Gameplay::SpawnAliens() {
//	for (int row = 0; row < ALIEN_FORMATION_HEIGHT; row++) {
//		for (int col = 0; col < ALIEN_FORMATION_WIDTH; col++) {
//			Alien newAlien = Alien(ALIEN_FORMATION_POS.x + ALIEN_OFFSET_X + (col * ALIEN_SPACING),
//						     ALIEN_FORMATION_POS.y + (row * ALIEN_SPACING),
//						     &_game->texturePack);
//			Aliens.push_back(newAlien);
//		}
//	}
}

void Gameplay::Render(Renderer& renderer) {
	for(auto& star : Stars) {
		star.Render(renderer);
	}
	renderer.DrawText(scoreText);
	renderer.DrawText(livesText);
	player.Render(renderer);
	for(auto& bunker: Bunkers) {
		bunker.Render(renderer);
	}
	alienSwarm.Render(renderer);
//	for (auto& alien : Aliens) {
//		alien.Render(renderer);
//	}
	for(auto& projectile : Projectiles) {
		projectile.Render(renderer);
	}
	if(paused) {
		renderer.DrawText("PAUSED", {500, 500}, 60);
	}
}

void Gameplay::CheckAllCollisions() {
	for(auto &projectile : Projectiles) {
		if (projectile.isActive()) {
			if(projectile.isPlayerProjectile()) {
				for(auto &alien : alienSwarm.getAliens()) {
					CheckCollision(alien, projectile);
				}
			}
			else if(projectile.isAlienProjectile() && projectile.isWithinPlayerRange()) {
				CheckCollision(player, projectile);
			}
			for(auto &bunker : Bunkers) {
				if(projectile.isWithinBunkerRange()) {
					CheckCollision(bunker, projectile);
				}
			}
		}
	}
}
void Gameplay::CheckCollision(Alien& alien, Projectile& projectile) {
	if (CheckCollision(alien.getCollider(), projectile.getCollider())) {
		projectile.hit();
		alien.hit();
		score += ALIEN_HIT_SCORE;
		scoreText.text = std::format("Score: {}", score);
	}
}
void Gameplay::CheckCollision(Player& player, Projectile& projectile) {
	if (CheckCollision(player.getCollider(), projectile.getCollider())) {
		projectile.hit();
		player.hit();
		livesText.text = std::format("Lives: {}", player.lives);
	}
}
void Gameplay::CheckCollision(Bunker& bunker, Projectile& projectile) {
	if (CheckCollision(bunker.getCollider(), projectile.getCollider())) {
		projectile.hit();
		bunker.hit();
	}
}
EndScreen::EndScreen(Game* game, int s) : GameScene(game), score(s) {
	if(_game == nullptr) { throw std::invalid_argument("_game == nullptr"); }
	newHighscore = _game->getLeaderboard().CheckNewHighscore(score);
}

EndScreen::~EndScreen() {
	assert(_game);
	_game->getLeaderboard().SaveToFile();
}

void EndScreen::Render(Renderer& renderer) {
	if (newHighscore) {
		RenderNewHighscore(renderer);
	}
	else {
		ShowScoreboard(renderer);
	}
}

void EndScreen::RenderNewHighscore(Renderer& renderer) {
	renderer.DrawText("NEW HIGHSCORE!", {600, 300}, 60, DEFAULT_FONT_COLOR);

	// BELOW CODE IS FOR NAME INPUT RENDER
	renderer.DrawText("PLACE MOUSE OVER INPUT BOX!", {600, 400}, HALF_FONT_SIZE);//, DEFAULT_FONT_COLOR);

	DrawRectangleRec(textBoxBounds, LIGHTGRAY);
	DrawRectangleLinesEx(textBoxBounds, 5, mouseOnText ? RED : DARKGRAY);

	renderer.DrawText(name, {textBoxBounds.x + 5, textBoxBounds.y + 8}, DEFAULT_FONT_SIZE, MAROON);

	//Draw the text explaining how many characters are used
	renderer.DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), {600, 600}, HALF_FONT_SIZE);//, DEFAULT_FONT_COLOR);

	if (mouseOnText) {
		if (letterCount < 9) {
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0) {
				renderer.DrawText("_", {textBoxBounds.x + 8 + MeasureText(name, DEFAULT_FONT_SIZE), textBoxBounds.y + 12});/*, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);*/
			}
		}
		else {
			//Name needs to be shorter
			renderer.DrawText("Press BACKSPACE to delete chars...", {600, 650}, HALF_FONT_SIZE);//, DEFAULT_FONT_COLOR);
		}
	}

	// Explain how to continue when name is input
	if (letterCount > 0 && letterCount < 9) {
		renderer.DrawText("PRESS ENTER TO CONTINUE", {600, 800});//, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
	}
}
void EndScreen::ShowScoreboard(Renderer& renderer) {
	// If no highscore or name is entered, show scoreboard and call it a day
	renderer.DrawText("PRESS ENTER TO CONTINUE", {600, 200});//, DEFAULT_FONT_SIZE, DEFAULT_FONT_COLOR);
	_game->getLeaderboard().Render(renderer);
}

std::optional<GameScene*> EndScreen::Update() {
	assert(_game != nullptr);
	if (IsKeyReleased(KEY_ENTER) && !newHighscore) { //Exit endscreen
		return new StartScreen(_game);
	}

	if (newHighscore) {
		mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBoxBounds);

		SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
		if (mouseOnText) {

			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0)
			{
				// NOTE: Only allow keys in range [32..125] //why not 126: '~' ?
				if ((key >= ASCII_SPACE) && (key <= ASCII_RIGHT_BRACKET) && (letterCount <= MAX_LETTER_COUNT)) {
					name[letterCount] = static_cast<char>(key);
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars
			if (IsKeyPressed(KEY_BACKSPACE)) {
				letterCount--;
				letterCount = std::clamp(letterCount, 0, MAX_LETTER_COUNT);
				name[letterCount] = '\0';
			}
			framesCounter++;
		}
		else {
			framesCounter = 0;
		}

		// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add
		// name + score to scoreboard
		if (letterCount > 0 && letterCount < MAX_LETTER_COUNT + 1 && IsKeyReleased(KEY_ENTER)) {
			std::string nameEntry(name);
			_game->getLeaderboard().InsertNewHighscore(nameEntry, score);
			newHighscore = false; //new high score was entered, high score updated
		}
	}
	return std::nullopt;
}

//void Gameplay::CleanUpEntities() {
//	std::erase_if(EnemyProjectiles, [](const EnemyProjectile& projectile) { return projectile.isHidden() || projectile.isOutOfBounds(); });
//	std::erase_if(PlayerProjectiles, [](const PlayerProjectile& projectile) { return projectile.isHidden() || projectile.isOutOfBounds(); });
//	alienSwarm.CleanUp();
//	std::erase_if(Walls, [](const Wall& wall) { return wall.isHidden(); });
//}
void Gameplay::RemoveInactiveEntities() {
	std::erase_if(Projectiles, [](auto& projectile) { return !projectile.isActive() || projectile.isOutOfBounds(); });
	alienSwarm.RemoveInactiveAliens();
//	std::erase_if(Aliens, [](auto& alien) { return alien.isDead(); });
	std::erase_if(Bunkers, [](auto& bunker) { return bunker.isDead(); });
}
void Gameplay::AliensShooting() {
	if (alienSwarm.empty()) {
		return;
	}
	alienShootTimer++;
	if (alienShootTimer < ALIEN_SHOOT_TIME) {
		return;
	}

//	int randomAlienIndex = GetRandomValue(0, static_cast<int>(Aliens.size()) - 1);

	Projectiles.push_back(Projectile(
						   Projectile::Type::Alien,
						   alienSwarm.getRandomAlienPosition(),
						   &_game->texturePack
						   )
				    );
	alienShootTimer = 0;
}

