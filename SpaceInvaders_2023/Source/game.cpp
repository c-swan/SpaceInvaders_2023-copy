#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <print>
#include "Constants.h"
#include "Math.hpp"


Game::Game() : textures() {

	//	Player(&textures.shipTextures[0]);
	//	textures = Textures();
	//Game Constructor... before loading scenes, although resources.Load should be in Resource constructor
	//	resources.Load(); //Textures constructor should construct
	//textures = Textures();

	//if(_scene == nullptr)
	_scene = new StartScreen(this);
	_scene->_game = this;
	SetTargetFPS(TARGET_FPS);               // Set our game to run at 60 frames-per-second
}

void Game::run() {
//	if(_scene == nullptr) _scene = new StartScreen(this);

	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}
}
//void Game::Start() { //start scene
//	// creating walls
//	//	float window_width = WINDOW_WIDTH; //TODO: window is not resizable, we do not need to keep getting screen bounds
//	//	float window_height = WINDOW_HEIGHT; //could this be member variable?
//
//	for (int i = 0; i < WALL_COUNT; i++) //wallCount should be constant
//	{
//		Wall newWalls(i);
//		Walls.push_back(newWalls);
//	}
//
//
//	//creating player TODO: why are we creating a new variable instead of player = Player()? also Initialize should be in constructor
////	player = Player();
//
//	//creating aliens
////	SpawnAliens();
//
//	background = Background();
//	//reset score
//	score = 0; //yeah
//
//	gameState = State::GAMEPLAY; //create Gameplay class?
//	//GameScene _scene;
//	//if(_scene != nullptr) delete _scene;
//	//_scene = new GameplayScene();
//	//_scene.OnEnter(*this);
//	//move Start function into GamePlayScene OnEnter() function
//
//}
//
//void Game::End() {
//	//SAVE SCORE AND UPDATE SCOREBOARD, in GameplayScene
//	PlayerProjectiles.clear(); //GameplayScene Destructor
//	EnemyProjectiles.clear(); //GameplayScene Destructor
//	Walls.clear();
//	Aliens.clear();
//
//	//Scene Transition
////	newHighScore = leaderboard.CheckNewHighScore(score);
////	gameState = State::ENDSCREEN;
//	//delete _scene;
//	//if(CheckNewHighScore) { _state = new EndScreen(highScore); }
//	//else _state = new EndScreen();
//}

//void Game::GameplayOnExit() {
//	leaderboard.SaveToFile();
//}
/*void Game::Continue() { //End->Start
 //	GameplayOnExit();
 gameState = State::STARTSCREEN;
 //	_scene
 }
 */
void Game::Update() {
	if(_scene == nullptr) return;
	if(_scene->_game == nullptr) _scene->_game = this;
	std::optional<GameScene*> status = _scene->Update();
	if(status.has_value()) {
		delete _scene;
		_scene = status.value();
		_scene->_game = this;
	}
}

//	switch (gameState) {
//	case State::STARTSCREEN:
//		StartScreenUpdate(); break;
//	case State::GAMEPLAY:
//		GameplayUpdate(); break;
//	case State::ENDSCREEN:
//		EndScreenUpdate(); break;
//	}
//_scene->Update(); }


void Game::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	if(_scene != nullptr) {
		_scene->Render();
	}
	EndDrawing();
}

//
//void Game::GameplayUpdate() {
//	if (IsKeyReleased(KEY_Q)) {
//		return End(); //quit
//	}
//	if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_PAUSE) || IsKeyReleased(KEY_P)) {
//		return Pause();
//	}
//	if(paused) {
//		return;
//	}
//	player.Update();
//	if (player.lives < 1){
//		return End(); //game over
//	}
//	//Update Aliens and Check if they are past player
//	for(auto &alien : Aliens) {
//		alien.Update();
//		if (alien.position.y > WINDOW_HEIGHT - PLAYER_BASE_HEIGHT) {
//			return End(); //game over
//		}
//	}
//
//	//Spawn new aliens if aliens run out
//	if (Aliens.size() < 1){
//		SpawnAliens();
//	}
//
//	background.setOffset(-player.getX() / PARALLAX_FACTOR);
//
//	//UPDATE PROJECTILE
//	for(auto &projectile : PlayerProjectiles) {
//		projectile.Update();
//	}
//	for(auto &projectile : EnemyProjectiles) {
//		projectile.Update();
//	}
//	//UPDATE PROJECTILE //Edit: Walls
//	for(auto &wall : Walls) {
//		//wall.Update();
//	}
//
//	//CHECK ALL COLLISONS HERE PLAYER_PROJECTILE-ALIENS
//	for (int i = 0; i < PlayerProjectiles.size(); i++)
//	{
//		LineSegment line = PlayerProjectiles[i].getLine();
//		for (int a = 0; a < Aliens.size(); a++)
//		{
//			//std::remove_if for each alien
//			//std::remove_if for each projectile
//			//erase remove_if's
//			if (CheckCollision(Aliens[a].position, ALIEN_RADIUS, line.start, line.end))
//			{
//				std::println("Hit!"); // Kill!
//				// Set them as inactive, will be killed later
//				PlayerProjectiles[i].hidden = true;
//				Aliens[a].hidden = true;
//				score += ALIEN_KILL_SCORE;
//			}
//		}
//
//		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
//		for(auto &wall : Walls)
//		{
//			if (CheckCollision(wall.position, WALL_RADIUS, line.start, line.end))
//			{
//				// Kill!
//				std::println("Hit!");
//				// Set them as inactive, will be killed later
//				PlayerProjectiles[i].hidden = true;
//				//					Walls[b].health -= 1;
//				wall.Hit();
//			}
//		}
//
//	}
//	//ENEMY PROJECTILES HERE		ENEMY_PROJECTILE-PLAYER
//	for (int i = 0; i < EnemyProjectiles.size(); i++)
//	{
//		LineSegment line = EnemyProjectiles[i].getLine();
//
//		if (CheckCollision(Circle{player.position, PLAYER_RADIUS}, line)) {
//			sounds.playHitSound();
//			std::println("dead");// << "dead!\n";
//			EnemyProjectiles[i].hidden = true;
//			player.lives--;
//			if(player.lives < 1) { return End(); } //game over
//		}
//
//		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
//		for(auto &wall : Walls)
//		{
//			if (CheckCollision(Circle{wall.position, WALL_RADIUS}, line)) {
//				// Kill!
//				std::println("Hit!");
//				// Set them as inactive, will be killed later
//				EnemyProjectiles[i].hidden = true;
//				//					Walls[b].health -= 1;
//				wall.Hit();
//			}
//		}
//	}
//
//	//MAKE PROJECTILE
//	if (IsKeyPressed(KEY_SPACE)) {
//		PlayerProjectile newPlayerProjetile({ player.getX(), WINDOW_HEIGHT - PROJECTILE_START_Y});
//		PlayerProjectiles.push_back(newPlayerProjetile);
//	}
//
////	AliensShooting();
//	cleanUpEntities();
//}
//
//void Game::GameplayRender() {
//	background.Render();
//	Render(player);
//
//	for (auto &wall : Walls) {
//		wall.Render(textures.barrierTexture);
//	}
//	for (auto &alien : Aliens) {
//		alien.Render(textures.alienTexture);
//	}
//	for(auto &projectile : PlayerProjectiles) {
//		projectile.Render(textures.laserTexture);
//	}
//	for(auto &projectile : EnemyProjectiles) {
//		projectile.Render(textures.laserTexture);
//	}
//
//	DrawText(TextFormat("Score: %i", score), 50, 20, DEFAULT_FONT_SIZE, TEXT_COLOR);
//	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, DEFAULT_FONT_SIZE, TEXT_COLOR);
//
//	if(paused) {
//		DrawTextCentered("PAUSED", HEADER_FONT_SIZE, TEXT_COLOR);
//	}
//}
//
//void Game::Render(const Sprite& sprite) {
//	if(sprite.hidden) return;
//	if(sprite._texture == nullptr) {
////		throw std::runtime_error("Sprite texture is nullptr");
//		return;
//	}
//	DrawTexturePro(*sprite._texture,
//			   sprite.bounds,
//			   sprite.bounds + sprite.position,
//			   getCenter(sprite.bounds),
//			   NO_ROTATION,
//			   NO_TINT);
//}


/*
 void Game::SpawnAliens() {
 for (int row = 0; row < FORMATION_HEIGHT; row++) {
 for (int col = 0; col < FORMATION_WIDTH; col++) {
 Alien newAlien = Alien(col, row);
 Aliens.push_back(newAlien);
 }
 }
 }


 void Game::cleanUpEntities() {
 // REMOVE INACTIVE/DEAD ENITITIES
 for (int i = 0; i < EnemyProjectiles.size(); i++) {
 //			if (Projectiles[i].active == false)
 if (!EnemyProjectiles[i].active)
 {
 EnemyProjectiles.erase(EnemyProjectiles.begin() + i);
 // Prevent the loop from skipping an instance because of index changes, since all insances after
 // the killed objects are moved down in index. This is the same for all loops with similar function
 i--;
 }
 }
 for (int i = 0; i < PlayerProjectiles.size(); i++) {
 //			if (Projectiles[i].active == false)
 if (!PlayerProjectiles[i].active)
 {
 PlayerProjectiles.erase(PlayerProjectiles.begin() + i);
 // Prevent the loop from skipping an instance because of index changes, since all insances after
 // the killed objects are moved down in index. This is the same for all loops with similar function
 i--;
 }
 }
 for (int i = 0; i < Aliens.size(); i++)
 {
 //			if (Aliens[i].active == false)
 if (!Aliens[i].active)
 {
 Aliens.erase(Aliens.begin() + i);
 i--;
 }
 }
 for (int i = 0; i < Walls.size(); i++)
 {
 //			if (Walls[i].active == false)
 if (!Walls[i].active)
 {
 Walls.erase(Walls.begin() + i);
 i--;
 }
 }
 }

 */
//Circle-LineSegment collision
//TODO: there exists a CheckCollisionPointCircle function in raylib...
//bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
//{
//	// our objective is to calculate the distance between the closest point on the line to the centre of the circle,
//	// and determine if it is shorter than the radius.
//
//	// check if either edge of line is within circle
//	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
//	{
//		return true;
//	}
//
//	// simplify variables
//	Vector2 A = lineStart;
//	Vector2 B = lineEnd;
//	Vector2 C = circlePos;
//
//	// calculate the length of the line
//	float length = lineLength(A, B);
//
//	// calculate the dot product  //what vectors...?
//	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / (length * length);
//
//	// use dot product to find closest point
//	float closestX = A.x + (dotP * (B.x - A.x));
//	float closestY = A.y + (dotP * (B.y - A.y));
//
//	//find out if coordinates are on the line.
//	// we do this by comparing the distance of the dot to the edges, with two vectors
//	// if the distance of the vectors combined is the same as the length the point is on the line
//
//	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
//	float buffer = 0.1;
//
//	float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
//	float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End
//
//	float closestLength = closeToStart + closeToEnd;
//
//	if (closestLength == length + buffer || closestLength == length - buffer)
//	{
//		//Point is on the line!
//
//		//Compare length between closest point and circle centre with circle radius
//
//		float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre
//
//		if (closeToCentre < circleRadius)
//		{
//			//Line is colliding with circle!
//			return true;
//		}
//		else
//		{
//			//Line is not colliding
//			return false;
//		}
//	}
//	else
//	{
//		// Point is not on the line, line is not colliding
//		return false;
//	}
//
//}

/*
 bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
 {
 // our objective is to calculate the distance between the closest point on the line to the centre of the circle,
 // and determine if it is shorter than the radius.

 // check if either edge of line is within circle
 if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
 {
 return true;
 }

 // simplify variables
 Vector2 A = lineStart;
 Vector2 B = lineEnd;
 Vector2 C = circlePos;

 // calculate the length of the line
 float length = lineLength(A, B);

 // calculate the dot product  AC
 float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2);
 // dot(C-A, B-A) / dot(B-A, B-A) = p, s.t. represents projection without vector (B-A)

 // use dot product to find closest point (on line?)
 float closestX = A.x + (dotP * (B.x - A.x)); //closest = A + p(B-A) = A + proj_AB(AC) = OA + AP = P
 float closestY = A.y + (dotP * (B.y - A.y));

 //find out if coordinates are on the line.
 // we do this by comparing the distance of the dot to the edges, with two vectors
 // if the distance of the vectors combined is the same as the length the point is on the line

 //since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
 float buffer = 0.1;

 float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
 float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End

 float closestLength = closeToStart + closeToEnd;

 if (closestLength == length + buffer || closestLength == length - buffer)
 {
 //Point is on the line!

 //Compare length between closest point and circle centre with circle radius

 float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre

 if (closeToCentre < circleRadius)
 {
 //Line is colliding with circle!
 return true;
 }
 else
 {
 //Line is not colliding
 return false;
 }
 }
 else
 {
 // Point is not on the line, line is not colliding
 return false;
 }

 } */

//
//void Game::DrawTextCenteredHorizontal(const char *text, int posY, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR) {
//	int halfTextWidth = MeasureText(text, fontSize) / 2;
//	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, posY, fontSize, color);
//}
//
//void Game::DrawTextCentered(const char *text, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR){        // Draw text (using default font)
//	int halfTextWidth = MeasureText(text, fontSize) / 2;
//	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, WINDOW_HEIGHT / 2, fontSize, color);
//}
//
//void Game::DrawTextCentered(const char *text, Vector2 offset, int fontSize = DEFAULT_FONT_SIZE, Color color = TEXT_COLOR) {       // Draw text (using default font)
//	int halfTextWidth = MeasureText(text, fontSize) / 2;
//	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth + offset.x, WINDOW_HEIGHT / 2 + offset.y, fontSize, color);
//}
