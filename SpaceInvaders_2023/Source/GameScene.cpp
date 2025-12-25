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

using namespace Render;

StartScreen::StartScreen(Game* game) : GameScene(game) {

}

StartScreen::~StartScreen() {

}


std::optional<GameScene*> StartScreen::Update() {
	if (IsKeyReleased(KEY_SPACE)) { return new Gameplay(_game); }
	return {};
}
void StartScreen::Render() {
	Render::DrawTextCenteredHorizontal("SPACE INVADERS", 100, TITLE_FONT_SIZE); //x:200, y:100
	Render::DrawTextCenteredHorizontal("PRESS SPACE TO BEGIN", 350, DEFAULT_FONT_SIZE); //200,350
}


Gameplay::Gameplay(Game* game) : GameScene(game) {
	_game = game;
	//if(game == nullptr) return;
	for (int i = 0; i < STAR_COUNT; i++) {
		Star newStar;
		Stars.push_back(newStar);
	}
	for (int i = 0; i < WALL_COUNT; i++) //wallCount should be constant
	{
		Wall newWalls(i, &_game->textures.barrierTexture);
		newWalls._texture = &_game->textures.barrierTexture;
		Walls.push_back(newWalls);
	}
	score = 0;
	player._texture = &game->textures.shipTextures[0];
}

//void Game::Start() { //start scene
	// creating walls
	//	float window_width = WINDOW_WIDTH; //TODO: window is not resizable, we do not need to keep getting screen bounds
	//	float window_height = WINDOW_HEIGHT; //could this be member variable?



	//creating player TODO: why are we creating a new variable instead of player = Player()? also Initialize should be in constructor
//	player = Player();

	//creating aliens
//	SpawnAliens();

//	background = Background();
	//reset score
//	score = 0; //yeah

//	gameState = State::GAMEPLAY; //create Gameplay class?
	//GameScene _scene;
	//if(_scene != nullptr) delete _scene;
	//_scene = new GameplayScene();
	//_scene.OnEnter(*this);
	//move Start function into GamePlayScene OnEnter() function

//}

Gameplay::~Gameplay() {
	PlayerProjectiles.clear(); //GameplayScene Destructor
	EnemyProjectiles.clear(); //GameplayScene Destructor
	Walls.clear();
	Aliens.clear();

}

std::optional<GameScene*> Gameplay::Update() {
	if (IsKeyReleased(KEY_Q)) {
		return new EndScreen(_game, score);
	}
	if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_PAUSE) || IsKeyReleased(KEY_P)) {
		Pause(); return {};
	}
	if(paused) {
		return {};
	}
	player.Update();
	if (player.lives < 1){
		return new EndScreen(_game, score);
	}
	//Update Aliens and Check if they are past player
	for(auto &alien : Aliens) {
		alien.Update();
		if (alien.getY() > WINDOW_HEIGHT - PLAYER_BASE_HEIGHT) {
			return new EndScreen(_game, score);
		}
	}

	SpawnAliens();

	star_offset_x = -player.getX() / PARALLAX_FACTOR;

	//UPDATE PROJECTILE
	for(auto &projectile : PlayerProjectiles) {
		projectile.Update();
	}
	for(auto &projectile : EnemyProjectiles) {
		projectile.Update();
	}
//	//UPDATE PROJECTILE //Edit: Walls
//	for(auto &wall : Walls) {
//		wall.Update();
//	}

	CheckAllCollisions();

	if(player.lives < 1) return new EndScreen(_game, score);

	//MAKE PROJECTILE
	if (IsKeyPressed(KEY_SPACE)) {
		PlayerProjectile newPlayerProjetile( &_game->textures.laserTexture,  { player.getX(), WINDOW_HEIGHT - PROJECTILE_START_Y});
		PlayerProjectiles.push_back(newPlayerProjetile);
	}

	AliensShooting();

	CleanUpEntities();
	return {};
}

void Gameplay::Render() {
	for(auto &star : Stars) {
		DrawCircleV(star.getPosition() + Vector2(star_offset_x, 0), star.getSize(), STAR_COLOR);
	}
	Render(player);
	for (auto &wall : Walls) {
		Render(wall);
		RenderWallText(wall);
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

	DrawText(TextFormat("Score: %i", score), 50, 20, DEFAULT_FONT_SIZE, TEXT_COLOR);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, DEFAULT_FONT_SIZE, TEXT_COLOR);

	if(paused) { Render::DrawTextCentered("PAUSED", HEADER_FONT_SIZE, TEXT_COLOR); }
}

void Gameplay::Render(const Sprite& sprite) {
	if(sprite.isHidden()) return;
	if(sprite._texture == nullptr) { // throw std::runtime_error("Sprite texture is nullptr");
		return;
	}
	DrawTexturePro(*sprite._texture,
			   sprite.getTextureRect(),
			   sprite.getBounds() + sprite.getPosition(),
			   getCenter(sprite.getBounds()),
			   NO_ROTATION,
			   NO_TINT);
}

void Gameplay::RenderWallText(const Wall &wall) {
	int textHalfWidth = MeasureText(TextFormat("%i", wall.getHealth()), DEFAULT_FONT_SIZE) / 2;
	DrawText(TextFormat("%i", wall.getHealth()), wall.getX() - textHalfWidth, wall.getY() + 10, DEFAULT_FONT_SIZE, WALL_TEXT_COLOR);
}

void Gameplay::CheckAllCollisions() {
	//CHECK ALL COLLISONS HERE PLAYER_PROJECTILE-Aliens
	for (int i = 0; i < PlayerProjectiles.size(); i++)
	{
		for (int a = 0; a < Aliens.size(); a++)
		{
			//std::remove_if for each alien
			//std::remove_if for each projectile
			//erase remove_if's
			if (CheckCollision(Circle(Aliens[a].getPosition(), ALIEN_RADIUS), PlayerProjectiles[i].getLine())) {
				std::println("Hit!");  // Set them as inactive, will be killed later
				PlayerProjectiles[i].Hit();
				Aliens[a].Hit();
				score += ALIEN_KILL_SCORE;
			}
		}

		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
		for(auto &wall : Walls) {
			if (CheckCollision(Circle(wall.getPosition(), WALL_RADIUS), PlayerProjectiles[i].getLine())) {
				std::println("Hit!"); // Set them as inactive, will be killed later
				PlayerProjectiles[i].Hit();
				//					Walls[b].health -= 1;
				wall.Hit();
			}
		}

	}

	//ENEMY PROJECTILES HERE		ENEMY_PROJECTILE-PLAYER
	for (int i = 0; i < EnemyProjectiles.size(); i++) {
		if (CheckCollision(Circle(player.getPosition(), PLAYER_RADIUS), EnemyProjectiles[i].getLine())) {
			_game->sounds.playHitSound();
			std::println("dead");// << "dead!\n";
			EnemyProjectiles[i].Hit();
			player.lives--;
			//if(player.lives < 1) { return new EndScreen(game, score); } //game over
		}

		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
		for(auto &wall : Walls)
		{
			if (CheckCollision(Circle(wall.getPosition(), WALL_RADIUS), EnemyProjectiles[i].getLine()))
			{
				// Kill!
				std::println("Hit!");
				// Set them as inactive, will be killed later
				EnemyProjectiles[i].Hit();
				//					Walls[b].health -= 1;
				wall.Hit();
			}
		}
	}
}

EndScreen::EndScreen(Game* game, int s) {
	_game = game;
	
	score = s;
	newHighScore = leaderboard.CheckNewHighScore(score);
}

EndScreen::~EndScreen() {
	leaderboard.SaveToFile();
}

void EndScreen::Render() {
	//DrawText("END", 50, 50, 40, YELLOW);
	if (!newHighScore) { // If no highscore or name is entered, show scoreboard and call it a day
		Render::DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", WINDOW_HEIGHT - 200, DEFAULT_FONT_SIZE, TEXT_COLOR);//200
		leaderboard.Render();
		return;
	}

	Render::DrawTextCenteredHorizontal("NEW HIGHSCORE!", 300, HEADER_FONT_SIZE, TEXT_COLOR); //y-pos = 300 down from
	Render::DrawTextCenteredHorizontal("PLACE MOUSE OVER INPUT BOX!", 400, HALF_FONT_SIZE, TEXT_COLOR);

	DrawRectangleRec(textBox, TEXTBOX_COLOR);

	Color inputFieldColor = (mouseOnText ? INPUT_ACTIVE_COLOR : INPUT_INACTIVE_COLOR);
	DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), inputFieldColor);

	//Draw the name being typed out
	DrawText(name, static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);

	//Draw the text explaining how many characters are used
	Render::DrawTextCenteredHorizontal(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, HALF_FONT_SIZE, TEXT_COLOR);

	if (mouseOnText) {
		if (letterCount < MAX_LETTER_COUNT) {
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0) {
				DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name, DEFAULT_FONT_SIZE), static_cast<int>(textBox.y) + 12, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);
			}
		}
		else
		{
			//Name needs to be shorter
			//DrawText("Press BACKSPACE to delete chars...", 600, 650, HALF_FONT_SIZE, TEXT_COLOR);
			Render::DrawTextCenteredHorizontal("Press BACKSPACE to delete chars...", 650, HALF_FONT_SIZE, TEXT_COLOR);
		}
	}

	// Explain how to continue when name is input
	if (letterCount > 0 && letterCount < MAX_LETTER_COUNT) {
		//DrawText("PRESS ENTER TO CONTINUE", 600, 800, DEFAULT_FONT_SIZE, TEXT_COLOR);
		Render::DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", 700, DEFAULT_FONT_SIZE, TEXT_COLOR); //800 out of bounds
	}
}

std::optional<GameScene*> EndScreen::Update() {
	if (IsKeyReleased(KEY_ENTER) && !newHighScore) { //Exit endscreen
		return new StartScreen(_game);
	}

	if (newHighScore) {
		mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

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
			leaderboard.InsertNewHighScore(nameEntry, score);
			newHighScore = false; //new high score was entered, high score updated
		}
	}
	return {};
}

void Gameplay::CleanUpEntities() {
	// REMOVE INACTIVE/DEAD SPRITE ENTITIES
	for (int i = 0; i < EnemyProjectiles.size(); i++) {
		if (EnemyProjectiles[i].isHidden()) {
			EnemyProjectiles.erase(EnemyProjectiles.begin() + i);
			// Prevent the loop from skipping an instance because of index changes, since all insances after
			// the killed objects are moved down in index. This is the same for all loops with similar function
			i--;
		}
	}
	for (int i = 0; i < PlayerProjectiles.size(); i++) {
		//			if (Projectiles[i].active == false)
		if (PlayerProjectiles[i].isHidden()) {
			PlayerProjectiles.erase(PlayerProjectiles.begin() + i);
			// Prevent the loop from skipping an instance because of index changes, since all insances after
			// the killed objects are moved down in index. This is the same for all loops with similar function
			i--;
		}
	}
	for (int i = 0; i < Aliens.size(); i++) {
		if (Aliens[i].isHidden()) {
			Aliens.erase(Aliens.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < Walls.size(); i++) {
		if (Walls[i].isHidden()) {
			Walls.erase(Walls.begin() + i);
			i--;
		}
	}
}

void Gameplay::SpawnAliens() {
	if(!Aliens.empty() || _game == nullptr) return;
	for (int row = 0; row < FORMATION_HEIGHT; row++) {
		for (int col = 0; col < FORMATION_WIDTH; col++) {
			Alien newAlien = Alien(col, row, &_game->textures.alienTexture);
			Aliens.push_back(newAlien);
		}
	}
}

void Gameplay::AliensShooting() {
	shootTimer += 1;
	if (shootTimer > TARGET_FPS - 1) { //once per second
		int randomAlienIndex = 0;

		if (Aliens.size() > 1) {
			randomAlienIndex = rand() % Aliens.size();
		}

		EnemyProjectile newEnemyProjectile(&_game->textures.laserTexture, Aliens[randomAlienIndex].getPosition());
		//		newEnemyProjectile.position.y += 40; //magic number
		EnemyProjectiles.push_back(newEnemyProjectile);
		shootTimer = 0;
	}
}
