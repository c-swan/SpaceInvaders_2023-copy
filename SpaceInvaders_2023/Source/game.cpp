#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <print>
#include "Constants.h"
#include "Math.hpp"

Game::Game() {

	//LOAD SOME RESOURCES HERE
	//Game Constructor... before loading scenes, although resources.Load should be in Resource constructor
	//	resources.Load(); //Textures constructor should construct
	SetTargetFPS(TARGET_FPS);               // Set our game to run at 60 frames-per-second

}

void Game::run() {
	while (!window.shouldClose()) {   // Detect window close button or ESC key
		Update();
		Render();
	}

}
void Game::Start() { //start scene
	// creating walls
	//	float window_width = WINDOW_WIDTH; //TODO: window is not resizable, we do not need to keep getting screen bounds
	//	float window_height = WINDOW_HEIGHT; //could this be member variable?

	for (int i = 0; i < WALL_COUNT; i++) //wallCount should be constant
	{
		Wall newWalls(i);
		Walls.push_back(newWalls);
	}


	//creating player TODO: why are we creating a new variable instead of player = Player()? also Initialize should be in constructor
	player = Player();

	//creating aliens
	SpawnAliens();

	background = Background();
	//reset score
	score = 0; //yeah

	gameState = State::GAMEPLAY; //create Gameplay class?
	//GameScene _scene;
	//if(_scene != nullptr) delete _scene;
	//_scene = new GameplayScene();
	//_scene.OnEnter(*this);
	//move Start function into GamePlayScene OnEnter() function

}

void Game::End() {
	//SAVE SCORE AND UPDATE SCOREBOARD, in GameplayScene
	PlayerProjectiles.clear(); //GameplayScene Destructor
	EnemyProjectiles.clear(); //GameplayScene Destructor
	Walls.clear();
	Aliens.clear();

	//Scene Transition
	newHighScore = leaderboard.CheckNewHighScore(score);
	gameState = State::ENDSCREEN;
	//delete _scene;
	//if(CheckNewHighScore) { _state = new EndScreen(highScore); }
	//else _state = new EndScreen();
}

void Game::Continue() {
	leaderboard.SaveToFile();
	gameState = State::STARTSCREEN; //
}


void Game::Update() {
	switch (gameState) {
	case State::STARTSCREEN:
		StartScreenUpdate(); break;
	case State::GAMEPLAY:
		GameplayUpdate(); break;
	case State::ENDSCREEN:
		EndScreenUpdate(); break;
	}
}


void Game::Render() {
	BeginDrawing();
	ClearBackground(BLACK);

	switch (gameState) {
	case State::STARTSCREEN:
		StartScreenRender(); break;
	case State::GAMEPLAY:
		GameplayRender(); break;
	case State::ENDSCREEN:
		EndScreenRender(); break;
	}

	EndDrawing();
}

void Game::GameplayUpdate() {
	if (IsKeyReleased(KEY_Q)) {
		return End(); //quit
	}
	if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_PAUSE) || IsKeyReleased(KEY_P)) {
		return Pause();
	}
	if(paused) {
		return;
	}
	player.Update();
	if (player.lives < 1){
		return End(); //game over
	}
	//Update Aliens and Check if they are past player
	for(auto &alien : Aliens) {
		alien.Update();
		if (alien.position.y > WINDOW_HEIGHT - PLAYER_BASE_HEIGHT) {
			return End(); //game over
		}
	}

	//Spawn new aliens if aliens run out
	if (Aliens.size() < 1){
		SpawnAliens();
	}

	background.setOffset(-player.getX() / PARALLAX_FACTOR);

	//UPDATE PROJECTILE
	for(auto &projectile : PlayerProjectiles) {
		projectile.Update();
	}
	for(auto &projectile : EnemyProjectiles) {
		projectile.Update();
	}
	//UPDATE PROJECTILE //Edit: Walls
	for(auto &wall : Walls) {
		wall.Update();
	}

	//CHECK ALL COLLISONS HERE PLAYER_PROJECTILE-ALIENS
	for (int i = 0; i < PlayerProjectiles.size(); i++)
	{
		for (int a = 0; a < Aliens.size(); a++)
		{
			//std::remove_if for each alien
			//std::remove_if for each projectile
			//erase remove_if's
			if (CheckCollision(static_cast<Vector2>(Aliens[a].position), ALIEN_RADIUS, PlayerProjectiles[i].lineStart, PlayerProjectiles[i].lineEnd))
			{
				std::println("Hit!"); // Kill!
				// Set them as inactive, will be killed later
				PlayerProjectiles[i].active = false;
				Aliens[a].active = false;
				score += ALIEN_KILL_SCORE;
			}
		}

		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
		for(auto &wall : Walls)
		{
			if (CheckCollision(static_cast<Vector2>(wall.position), WALL_RADIUS, PlayerProjectiles[i].lineStart, PlayerProjectiles[i].lineEnd))
			{
				// Kill!
				std::println("Hit!");
				// Set them as inactive, will be killed later
				PlayerProjectiles[i].active = false;
				//					Walls[b].health -= 1;
				wall.health--;
			}
		}

	}
	//ENEMY PROJECTILES HERE		ENEMY_PROJECTILE-PLAYER
	for (int i = 0; i < EnemyProjectiles.size(); i++)
	{

		if (CheckCollision(static_cast<Vector2>(player.position), PLAYER_RADIUS, EnemyProjectiles[i].lineStart, EnemyProjectiles[i].lineEnd))
		{
			sounds.playHitSound();
			std::println("dead");// << "dead!\n";
			EnemyProjectiles[i].active = false;
			player.lives--;
			if(player.lives < 1) { return End(); } //game over
		}

		//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
		for(auto &wall : Walls)
		{
			if (CheckCollision(static_cast<Vector2>(wall.position), WALL_RADIUS, EnemyProjectiles[i].lineStart, EnemyProjectiles[i].lineEnd))
			{
				// Kill!
				std::println("Hit!");
				// Set them as inactive, will be killed later
				EnemyProjectiles[i].active = false;
				//					Walls[b].health -= 1;
				wall.health--;
			}
		}
	}




	//MAKE PROJECTILE
	if (IsKeyPressed(KEY_SPACE)) {
		PlayerProjectile newPlayerProjetile({ player.getX(), WINDOW_HEIGHT - PROJECTILE_START_Y});
		PlayerProjectiles.push_back(newPlayerProjetile);
	}

	//Aliens Shooting
	shootTimer += 1;
	if (shootTimer > TARGET_FPS - 1) //once per second
	{
		int randomAlienIndex = 0;

		if (Aliens.size() > 1) {
			randomAlienIndex = rand() % Aliens.size();
		}

		EnemyProjectile newEnemyProjectile(Aliens[randomAlienIndex].position);
//		newEnemyProjectile.position.y += 40; //magic number
		EnemyProjectiles.push_back(newEnemyProjectile);
		shootTimer = 0;
	}

	cleanUpEntities();
}
void Game::GameplayRender() {
	background.Render();
	player.Render(textures.shipTextures[player.activeTexture]);

	for (auto &wall : Walls) {
		wall.Render(textures.barrierTexture);
	}
	for (auto &alien : Aliens) {
		alien.Render(textures.alienTexture);
	}
	for(auto &projectile : PlayerProjectiles) {
		projectile.Render(textures.laserTexture);
	}
	for(auto &projectile : EnemyProjectiles) {
		projectile.Render(textures.laserTexture);
	}

	DrawText(TextFormat("Score: %i", score), 50, 20, DEFAULT_FONT_SIZE, TEXT_COLOR);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, DEFAULT_FONT_SIZE, TEXT_COLOR);

	if(paused) {
		DrawTextCentered("PAUSED", HEADER_FONT_SIZE, TEXT_COLOR);
	}
}
void Game::StartScreenUpdate() {
	if (IsKeyReleased(KEY_SPACE)) {
		Start();
	}
}
void Game::StartScreenRender() {
	//const char *text, int posX, int posY, int fontSize, Color color       // Draw text (using default font)
	DrawTextCenteredHorizontal("SPACE INVADERS", 100, TITLE_FONT_SIZE, TEXT_COLOR); //x:200, y:100
	DrawTextCenteredHorizontal("PRESS SPACE TO BEGIN", 350, DEFAULT_FONT_SIZE, TEXT_COLOR); //200, 350
}
void Game::EndScreenRender() {
	//DrawText("END", 50, 50, 40, YELLOW);
	if (newHighScore) {
		//TODO: make UI scalable
		//default aligned x = 600
		DrawTextCenteredHorizontal("NEW HIGHSCORE!", 300, HEADER_FONT_SIZE, TEXT_COLOR); //y-pos = 300 down from

		// BELOW CODE IS FOR NAME INPUT RENDER
		DrawTextCenteredHorizontal("PLACE MOUSE OVER INPUT BOX!", 400, HALF_FONT_SIZE, TEXT_COLOR);

		DrawRectangleRec(textBox, TEXTBOX_COLOR);

		Color inputFieldColor = (mouseOnText ? INPUT_ACTIVE_COLOR : INPUT_INACTIVE_COLOR);
		DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), inputFieldColor);

		//Draw the name being typed out
		DrawText(name, static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);

		//Draw the text explaining how many characters are used
		DrawTextCenteredHorizontal(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, HALF_FONT_SIZE, TEXT_COLOR);

		if (mouseOnText)
		{
			if (letterCount < MAX_LETTER_COUNT)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0)
				{
					DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name, DEFAULT_FONT_SIZE), static_cast<int>(textBox.y) + 12, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);
				}

			}
			else
			{
				//Name needs to be shorter
				//DrawText("Press BACKSPACE to delete chars...", 600, 650, HALF_FONT_SIZE, TEXT_COLOR);
				DrawTextCenteredHorizontal("Press BACKSPACE to delete chars...", 650, HALF_FONT_SIZE, TEXT_COLOR);
			}

		}

		// Explain how to continue when name is input
		if (letterCount > 0 && letterCount < MAX_LETTER_COUNT)
		{
			//DrawText("PRESS ENTER TO CONTINUE", 600, 800, DEFAULT_FONT_SIZE, TEXT_COLOR);
			DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", 700, DEFAULT_FONT_SIZE, TEXT_COLOR); //800 out of bounds
		}
	}
	else {
		// If no highscore or name is entered, show scoreboard and call it a day
		DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", WINDOW_HEIGHT - 200, DEFAULT_FONT_SIZE, TEXT_COLOR);//200

		leaderboard.Render();
	}
}

void Game::EndScreenUpdate() {
	if (IsKeyReleased(KEY_ENTER) && !newHighScore) { //Exit endscreen
		Continue();
	}

	if (newHighScore) {
		mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

		SetMouseCursor((mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT));
		if (mouseOnText) {

			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0)
			{
				// NOTE: Only allow keys in range [32..125] //why not 126: '~' ?
				if ((key >= ASCII_SPACE) && (key <= ASCII_RIGHT_BRACKET) && (letterCount < MAX_LETTER_COUNT))
				{
					name[letterCount] = (char)key;
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars
			if (IsKeyPressed(KEY_BACKSPACE))
			{
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
}
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

void Game::Pause() {
	paused = !paused;
}

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
bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	// our objective is to calculate the distance between the closest point on the line to the centre of the circle,
	// and determine if it is shorter than the radius.

	// check if either edge of line is within circle
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd)) { return true; }


	// simplify variables

	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate the length of the line
	float length = lineLength(A, B);

	// calculate the dot product  //what vectors...?
	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / (length * length);

	// use dot product to find closest point
	float closestX = A.x + (dotP * (B.x - A.x));
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

}

Game::~Game() {

}
void Game::DrawTextCenteredHorizontal(const char *text, int posY, int fontSize, Color color) {
	int halfTextWidth = MeasureText(text, fontSize) / 2;
	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, posY, fontSize, color);
}

void Game::DrawTextCentered(const char *text, int fontSize, Color color){        // Draw text (using default font)
	int halfTextWidth = MeasureText(text, fontSize) / 2;
	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth, WINDOW_HEIGHT / 2, fontSize, color);
}

void Game::DrawTextCentered(const char *text, Vector2 offset, int fontSize, Color color){       // Draw text (using default font)
	int halfTextWidth = MeasureText(text, fontSize) / 2;
	DrawText(text, (WINDOW_WIDTH / 2) - halfTextWidth + offset.x, WINDOW_HEIGHT / 2 + offset.y, fontSize, color);
}


/*LEGACY CODE
 // our objective is to calculate the distance between the closest point of the line to the centre of the circle,
 // and determine if it is shorter than the radius.

 // we can imagine the edges of the line and circle centre to form a triangle. calculating the height of the
 // triangle will give us the distance, if the line serves as the base

 // simplify variables
 Vector2 A = lineStart;
 Vector2 B = lineEnd;
 Vector2 C = circlePos;

 // calculate area using determinant method

 float triangle_area = fabsf(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2;


 // Caculate vectors AB to calculate base length
 Vector2 AB;
 AB.x = B.x - A.x;
 AB.y = B.y - A.y;

 //get the base length
 float trangle_base_length = (float)sqrt(pow(AB.x, 2) + pow(AB.y, 2));

 // we double the area to turn in into a rectangle, and then divide the base length to get the height.
 float triangle_height = (triangle_area * 2 ) / trangle_base_length;

 std::cout << triangle_area << "\n";

 if (triangle_height < circleRadius)
 {
 return true;
 }
 else
 {
 return false;
 }


 */

