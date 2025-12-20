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
void Game::Start()
{
	// creating walls
	//	float window_width = WINDOW_WIDTH; //TODO: window is not resizable, we do not need to keep getting screen bounds
	//	float window_height = WINDOW_HEIGHT; //could this be member variable?
	float wall_distance = WINDOW_WIDTH / (WALL_COUNT + 1);

	for (int i = 0; i < WALL_COUNT; i++) //wallCount should be constant
	{
		Wall newWalls;
		newWalls.active = true;
		newWalls.position.y = WINDOW_HEIGHT - WALL_BASE_HEIGHT;
		newWalls.position.x = wall_distance * (i + 1);

		Walls.push_back(newWalls);
	}


	//creating player TODO: why are we creating a new variable instead of player = Player()? also Initialize should be in constructor
	Player newPlayer;
	player = newPlayer;
	player.Initialize();

	//creating aliens
	SpawnAliens();

	//creating background
	Background newBackground;
	newBackground.Initialize(); //use constant star_count, use Background constructor instead
	background = newBackground;

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
	Projectiles.clear(); //GameplayScene Destructor
	Walls.clear();
	Aliens.clear();

	//Scene Transition
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
	//delete _scene;
	//if(CheckNewHighScore) { _state = new EndScreen(highScore); }
	//else _state = new EndScreen();
}

void Game::Continue() {

	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}


void Game::Update() {//separate into different functions
	switch (gameState) {
	case State::STARTSCREEN: //(StartScene)_state->Update();
		if (IsKeyReleased(KEY_SPACE)) {
			Start();
		}
		break;
	case State::GAMEPLAY: //(GameplayScene)_state->Update();
		//Code
		if (IsKeyReleased(KEY_Q)) {
			End(); return; //quit game
		}
		if (IsKeyReleased(KEY_ENTER) || IsKeyReleased(KEY_PAUSE) || IsKeyReleased(KEY_P)) {
			Pause(); return;
		}
		if(paused) {
			return;
		}
		player.Update();

		//Update Aliens and Check if they are past player
		for (int i = 0; i < Aliens.size(); i++)
		{
			Aliens[i].Update();

			if (Aliens[i].position.y > WINDOW_HEIGHT - PLAYER_BASE_HEIGHT)
			{
				End(); //game over
			}
		}

		//End game if player dies
		if (player.lives < 1)
		{
			End(); //game over
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}


		// Update background with offset
		//point playerPos = player.position;
		//		Vector2 cornerPos = { 0, PLAYER_BASE_HEIGHT };
		//playerPos, cornerPos have same y, distance will be player.x_pos - 0
		{
			float offsetX = - player.getX(); //offset is background position basically
			background.setOffset(offsetX / PARALLAX_FACTOR);
			background.Update();
		}

		//UPDATE PROJECTILE
		for (int i = 0; i < Projectiles.size(); i++)
		{
			Projectiles[i].Update();
		}
		//UPDATE PROJECTILE //Edit: Walls
		for (int i = 0; i < Walls.size(); i++)
		{
			Walls[i].Update();
		}

		//CHECK ALL COLLISONS HERE PLAYER_PROJECTILE-ALIENS
		for (int i = 0; i < Projectiles.size(); i++)
		{
			if (Projectiles[i].type == ProjectileType::PLAYER_PROJECTILE)
			{
				for (int a = 0; a < Aliens.size(); a++)
				{
					//std::remove_if for each alien
					//std::remove_if for each projectile
					//erase remove_if's
					if (CheckCollision(static_cast<Vector2>(Aliens[a].position), ALIEN_RADIUS, Projectiles[i].lineStart, Projectiles[i].lineEnd))
					{
						std::println("Hit!"); // Kill!
						// Set them as inactive, will be killed later
						Projectiles[i].active = false;
						Aliens[a].active = false;
						score += ALIEN_KILL_SCORE;
					}
				}
			}

			//ENEMY PROJECTILES HERE		ENEMY_PROJECTILE-PLAYER
			for (int i = 0; i < Projectiles.size(); i++)
			{
				if (Projectiles[i].type == ProjectileType::ENEMY_PROJECTILE)
				{
					if (CheckCollision(static_cast<Vector2>(player.position), player.radius, Projectiles[i].lineStart, Projectiles[i].lineEnd))
					{
						sounds.playHitSound();
						std::println("dead");// << "dead!\n";
						Projectiles[i].active = false;
						player.lives -= 1;
					}
				}
			}

			//WALLS–ENEMY_PROJECTILES & WALLS–PLAYER_PROJECTILES
			for (int b = 0; b < Walls.size(); b++)
			{
				if (CheckCollision(static_cast<Vector2>(Walls[b].position), WALL_RADIUS, Projectiles[i].lineStart, Projectiles[i].lineEnd))
				{
					// Kill!
					std::println("Hit!");
					// Set them as inactive, will be killed later
					Projectiles[i].active = false;
					//					Walls[b].health -= 1;
					Walls[b].health--;
				}
			}
		}

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			float window_height = (float)WINDOW_HEIGHT;
			Projectile newProjectile;
			newProjectile.position.x = player.getX();
			newProjectile.position.y = window_height - 130;
			newProjectile.type = ProjectileType::PLAYER_PROJECTILE;
			Projectiles.push_back(newProjectile);
		}

		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > TARGET_FPS - 1) //once per second
		{
			int randomAlienIndex = 0;

			if (Aliens.size() > 1)
			{
				randomAlienIndex = rand() % Aliens.size();
			}

			Projectile newProjectile;
			newProjectile.position = Aliens[randomAlienIndex].position;
			newProjectile.position.y += 40; //magic number
			newProjectile.speed = PROJECTILE_SPEED;
			newProjectile.type = ProjectileType::ENEMY_PROJECTILE;
			Projectiles.push_back(newProjectile);
			shootTimer = 0;
		}

		// REMOVE INACTIVE/DEAD ENITITIES
		for (int i = 0; i < Projectiles.size(); i++)
		{
			//			if (Projectiles[i].active == false)
			if (!Projectiles[i].active)
			{
				Projectiles.erase(Projectiles.begin() + i);
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
		break;
	case State::ENDSCREEN:
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore) {
			Continue();
		}

		if (newHighScore) {
			mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);

			if (mouseOnText) {
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed on the queue
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
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add
			// name + score to scoreboard
			if (letterCount > 0 && letterCount < MAX_LETTER_COUNT && IsKeyReleased(KEY_ENTER))
			{
				std::string nameEntry(name);
				InsertNewHighScore(nameEntry);
				newHighScore = false; //new high score was entered, no more new high score
			}
		}
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}


void Game::Render() { //do not return without EndDrawing();
	BeginDrawing();
	ClearBackground(BLACK); //TODO: delegate to Game

	switch (gameState)
	{
	case State::STARTSCREEN:
		//const char *text, int posX, int posY, int fontSize, Color color       // Draw text (using default font)
		DrawTextCenteredHorizontal("SPACE INVADERS", 100, TITLE_FONT_SIZE, TEXT_COLOR); //x:200, y:100
		DrawTextCenteredHorizontal("PRESS SPACE TO BEGIN", 350, DEFAULT_FONT_SIZE, TEXT_COLOR); //200, 350
		break;
	case State::GAMEPLAY:
		//background render LEAVE THIS AT TOP
		background.Render();

		//player rendering
		player.Render(textures.shipTextures[player.activeTexture]);

		//projectile rendering
		for (int i = 0; i < Projectiles.size(); i++)
		{
			Projectiles[i].Render(textures.laserTexture);
		}

		// wall rendering
		for (int i = 0; i < Walls.size(); i++)
		{
			Walls[i].Render(textures.barrierTexture);
		}

		//alien rendering
		for (int i = 0; i < Aliens.size(); i++)
		{
			Aliens[i].Render(textures.alienTexture);
		}

		//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
		DrawText(TextFormat("Score: %i", score), 50, 20, DEFAULT_FONT_SIZE, TEXT_COLOR);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, DEFAULT_FONT_SIZE, TEXT_COLOR);

		if(paused)
		{
			DrawTextCentered("PAUSED", HEADER_FONT_SIZE, TEXT_COLOR);
		}
		break;
	case State::ENDSCREEN:
		//DrawText("END", 50, 50, 40, YELLOW);
		if (newHighScore)
		{
			//TODO: make UI scalable
			//default aligned x = 600
			DrawTextCenteredHorizontal("NEW HIGHSCORE!", 300, HEADER_FONT_SIZE, TEXT_COLOR); //y-pos = 300 down from

			// BELOW CODE IS FOR NAME INPUT RENDER
			DrawTextCenteredHorizontal("PLACE MOUSE OVER INPUT BOX!", 400, HALF_FONT_SIZE, TEXT_COLOR);

			DrawRectangleRec(textBox, TEXTBOX_COLOR);

			Color inputFieldColor = (mouseOnText ? INPUT_ACTIVE_COLOR : INPUT_INACTIVE_COLOR);
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, inputFieldColor);

			//Draw the name being typed out
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);

			//Draw the text explaining how many characters are used
			DrawTextCenteredHorizontal(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, HALF_FONT_SIZE, TEXT_COLOR);

			if (mouseOnText)
			{
				if (letterCount < MAX_LETTER_COUNT)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, DEFAULT_FONT_SIZE), (int)textBox.y + 12, DEFAULT_FONT_SIZE, TEXT_INPUT_COLOR);
					}

				}
				else
				{
					//Name needs to be shorter
					//					DrawText("Press BACKSPACE to delete chars...", 600, 650, HALF_FONT_SIZE, TEXT_COLOR);
					DrawTextCenteredHorizontal("Press BACKSPACE to delete chars...", 650, HALF_FONT_SIZE, TEXT_COLOR);
				}

			}

			// Explain how to continue when name is input
			if (letterCount > 0 && letterCount < MAX_LETTER_COUNT)
			{
				//				DrawText("PRESS ENTER TO CONTINUE", 600, 800, DEFAULT_FONT_SIZE, TEXT_COLOR);
				DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", 700, DEFAULT_FONT_SIZE, TEXT_COLOR); //800 out of bounds
			}
		}
		else {
			// If no highscore or name is entered, show scoreboard and call it a day
			//			DrawText("PRESS ENTER TO CONTINUE", 600, 200, DEFAULT_FONT_SIZE, TEXT_COLOR);
			DrawTextCenteredHorizontal("PRESS ENTER TO CONTINUE", WINDOW_HEIGHT - 200, DEFAULT_FONT_SIZE, TEXT_COLOR);//200

			DrawText("LEADERBOARD", 50, 100, DEFAULT_FONT_SIZE, TEXT_COLOR);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				char* tempNameDisplay = Leaderboard[i].name.data();
				DrawText(tempNameDisplay, 50, 140 + (i * 40), DEFAULT_FONT_SIZE, TEXT_COLOR);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), DEFAULT_FONT_SIZE, TEXT_COLOR);
			}
		}
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}

	EndDrawing();

}

void Game::SpawnAliens() {
	for (int row = 0; row < FORMATION_HEIGHT; row++) {
		for (int col = 0; col < FORMATION_WIDTH; col++) {
			Alien newAlien = Alien(col, row);
			Aliens.push_back(newAlien);
		}
	}
}

bool Game::CheckNewHighScore() {
	return (score > Leaderboard[4].score); //return this
}

void Game::InsertNewHighScore(std::string name)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++) { //TODO: for ranged loop

		if (newData.score > Leaderboard[i].score)
		{
			Leaderboard.insert(Leaderboard.begin() + i, newData);
			Leaderboard.pop_back();
			//			i = Leaderboard.size(); //exit loop
			return;
		}
	}
}

void Game::LoadLeaderboard() {

	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::Pause() {
	paused = !paused;
}
void Game::SaveLeaderboard() {

	// SAVE LEADERBOARD AS ARRAY //clarification...?
	/*
	 {
	 "Leaderboard" : [
	 { "name":"Player 1", "score":2000 },
	 { "name":"Player 2", "score":1000 },
	 { "name":"Player 3", "score":500 },
	 { "name":"Player 4", "score":200 },
	 { "name":"Player 5", "score":100 },
	 ]
	 }
	 */

	// OPEN FILE
	std::ofstream file; //fstream -> ofstream, to create file if doesn't exist

	file.open("./Leaderboard.txt"); //use relative path and txt extension, why not

	if (!file) {
		std::println("file not found");
	}
	else {
		std::println("file found");
	}

	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
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
void Player::Initialize()  {
	//float window_width = (float)WINDOW_WIDTH;
	position.x = WINDOW_WIDTH / 2;
	position.y = WINDOW_HEIGHT - PLAYER_BASE_HEIGHT;
	std::println("Find Player {}", position);
}

void Player::Update()
{

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT)) //interesting implementation...
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += PLAYER_SPEED * direction;

	if (getX() < 0 + PLAYER_RADIUS) //TODO: Clamp
	{
		position.x = 0 + PLAYER_RADIUS;
	}
	else if (getX() > WINDOW_WIDTH - PLAYER_RADIUS)
	{
		position.x = WINDOW_WIDTH - PLAYER_RADIUS;
	}


	//Determine frame for animation
	animationTimer += GetFrameTime();

	if (animationTimer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		animationTimer = 0;
	}
	else if (animationTimer > 0.4)
	{
		activeTexture++;
		animationTimer = 0;
	}


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
void Player::Render(Texture2D texture) {
	//Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint
	DrawTexturePro(texture,
			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect),
			   NO_ROTATION,
			   NO_TINT);
}



void Projectile::Update() {
	position.y += speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - PROJECTILE_LENGTH / 2; //TODO: these are tied to constants, use getter function
	lineEnd.y   = position.y + PROJECTILE_LENGTH / 2;		//getLineEnd() { Vector2 lineStart = position; lineStart.y -= 15; }

	lineStart.x = position.x;
	lineEnd.x   = position.x;

	if (position.y < 0 || position.y > PROJECTILE_BOUNDS ) //Out of bounds (more magical numbers :D
	{
		active = false;
	}
}

void Projectile::Render(Texture2D texture)
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
	DrawTexturePro(texture,
			   getBounds(PROJECTILE_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect), //origin
			   NO_ROTATION,
			   NO_TINT);
}

void Wall::Render(Texture2D texture)
{
	DrawTexturePro(texture,
			   getBounds(WALL_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect), //origin = dimensions / 2
			   NO_ROTATION,
			   NO_TINT);

	int textHalfWidth = MeasureText(TextFormat("%i", health), DEFAULT_FONT_SIZE) / 2;
	DrawText(TextFormat("%i", health), position.x-textHalfWidth, position.y+10, DEFAULT_FONT_SIZE, WALL_TEXT_COLOR);

}

void Wall::Update() {
	// set walls as inactive when out of health
	// use setter instead of detecting health value
	if (health < 1)
	{
		active = false;
	}
}

Alien::Alien(int col, int row) {
	position.x = FORMATION_X + ALIEN_PADDING_X + (col * ALIEN_SPACING);
	position.y = FORMATION_Y + (row * ALIEN_SPACING);
	active = true;
	std::println("Alien Spawned, Row:{}, Column:{}, Position: {}", row, col, position);
}
void Alien::Update() {

	float direction = moveRight ? 1 : -1;
	if (moveRight)
	{
		position.x += ALIEN_SPEED * direction;

		if (position.x >= WINDOW_WIDTH) //touching right edge
		{
			moveRight = false; //moveRight is true, moveRight = false, moveRight = !moveRight;
			position.y += ALIEN_MOVEMENT_Y; //move down  //originally 50 but looks weird
		}
	}
	else
	{
		position.x += ALIEN_SPEED * direction;

		if (position.x <= 0) //touching left edge
		{
			moveRight = true; //moveRight is false, moveRight = true, moveRight = !moveRight;
			position.y += ALIEN_MOVEMENT_Y; //move down
		}
	}
}

void Alien::Render(Texture2D texture)
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);

	DrawTexturePro(texture,
			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect),
			   NO_ROTATION,
			   NO_TINT);
}


//BACKGROUND
void Star::Update() {
	//position.x = position.x + localPosition.x;
}

void Star::Render() {
	//DrawCircleV((int)position.x, (int)position.y, size, color);
	DrawCircleV(static_cast<Vector2>(position + localPosition), size, color);
}


void Background::Initialize() { //TODO: Star Constrcutor, and star count constant
	for (int i = 0; i < STAR_COUNT; i++) {
		Star newStar;
		newStar.position = position; //parent position / offset
		newStar.localPosition.x = GetRandomValue(-BACKGROUND_EDGE_SIZE, WINDOW_WIDTH + BACKGROUND_EDGE_SIZE);
		newStar.localPosition.y = GetRandomValue(0, WINDOW_HEIGHT);

		newStar.color = STAR_COLOR; //random color? //sure!

		newStar.size = GetRandomValue(1, STAR_MAX_SIZE * 2) / 2;

		Stars.push_back(newStar);
	}
}

void Background::setOffset(float offsetX) {
	position.x = offsetX;
	for(auto &star : Stars) {
		star.position.x = offsetX;
	}
}
void Background::Update() {
	for(auto &star : Stars) {
		star.Update();
	}
}

void Background::Render() {
	for(auto &star : Stars) {
		star.Render();
	}
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

