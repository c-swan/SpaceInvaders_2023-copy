#pragma once
#include "raylib.h"
#include <vector>
#include "Textures.hpp"
#include "Sounds.hpp"
#include <string>
#include "Constants.h"
#include "Math.hpp"
#include "Window.hpp"
#include "Sounds.hpp"
#include "GameScene.hpp"
#include "Leaderboard.hpp"
#include "Entities.hpp"

//TODO: separate classes / structs into files
enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

class Game {
	public:
	Game();
	~Game();

	void run();

	State gameState = State::STARTSCREEN;

	int score = 0;
	float shootTimer = 0; //Aliens shooting

	bool newHighScore = false;

	void Start(); //StartScreen -> Gameplay
	void End(); // Gameplay -> EndScreen

	void Pause(); //new functionality (Gameplay)

	void Continue(); //EndScreen -> StartScreen
//	void Launch(); //constructor

	void Update();
	void Render();

	void GameplayUpdate();
	void GameplayRender();
	
	void StartScreenUpdate();
	void StartScreenRender();

	void EndScreenUpdate();
	void EndScreenRender();

	void DrawTextCentered(const char *text, int fontSize, Color color);
	void DrawTextCentered(const char *text, Vector2 offset, int fontSize, Color color);
	void DrawTextCenteredHorizontal(const char *text, int posY, int fontSize, Color color);

	void SpawnAliens();
	void cleanUpEntities();

	void checkAllCollisions();
	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);


//high-score / leaderboard

	// Entity Storage and Resources
	Window window;
	Textures textures;
	Sounds sounds;

	Player player;
	std::vector<EnemyProjectile> EnemyProjectiles; //TODO: separate into PlayerProjectiles and EnemyProjectiles and get rid of EntityType
	std::vector<PlayerProjectile> PlayerProjectiles; //TODO: separate into PlayerProjectiles and EnemyProjectiles and get rid of EntityType
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	Background background;

	bool paused = false;

	GameScene* _scene = nullptr;

	Leaderboard leaderboard;
	//TEXTBOX ENTER
	char name[MAX_LETTER_COUNT + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};
