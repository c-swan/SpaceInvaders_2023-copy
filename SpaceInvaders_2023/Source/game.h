#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include "Window.hpp"
#include "AudioAssets.hpp"

#include <string>
#include <print>
enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData
{
	std::string name;
	int score;
};

struct Player
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;  
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER;

	void Initialize();
	void Render(Texture2D texture);
	void Update();
	
};


struct Projectile
{
public: 
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position = {0,0};
	int speed = 15; 
	bool active = true;  
	EntityType type = {};

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();

	void Render(Texture2D texture);
};

struct Wall 
{
public: 
	Vector2 position; 
	Rectangle rec; 
	bool active; 
	Color color; 
	int health = 50;
	int radius = 60;


	void Render(Texture2D texture); 
	void Update(); 
};

struct Alien
{
public:
	
	Color color = WHITE; 
	Vector2 position = {0, 0};
	int x = 0; 
	int y = 0; 
	float radius = 30;
	bool active = true;  
	bool moveRight = true; 
	
	EntityType type = EntityType::ENEMY; 

	int speed = 2; 
		 
	void Update(); 
	void Render(Texture2D texture); 
};


struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	void Update(float starOffset);
	void Render();
};

struct Background
{
	

	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render();

};

class Game {
	public:
	Game() {
		SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	}
	~Game() {}

	Window window;
	Resources resources;
	AudioAssets audioAssets;

	inline void playSounds() {
		if (IsKeyPressed(KEY_SPACE)) {
			PlaySound(audioAssets.sound);
		}
		if (IsKeyPressed(KEY_BACKSPACE)) {
			StopSound(audioAssets.sound);
		}
	}
	inline void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);
		Render(); //Draw and Render need not be separated
		EndDrawing();
	}
	//...

	// Gamestate
	State gameState = State::STARTSCREEN;

	int score = 0;
	float alienShootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 };

	bool newHighScore = false;

	void Start();
	void End();

	void Continue();
	void Launch();

	void Update();
	void Render();

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	bool CheckNewHighScore() { return (score > Leaderboard.back().score); }

	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();

	Player player;

	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	
	Background background;


	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};
