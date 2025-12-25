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
	~Game() { if(_scene) delete _scene; }

	void Run();

	//State gameState = State::STARTSCREEN;

//	int score = 0;
//	float shootTimer = 0; //Aliens shooting
//
//	bool newHighScore = false; //TODO: probably don't need this bool

//	void Start(); //StartScreen -> Gameplay
//	void End(); // Gameplay -> EndScreen
//
//	void Continue(); //EndScreen -> StartScreen
//	void Launch(); //constructor ...?

//	void Input();
	void Update();
	void Render();
	void Render(const Sprite& sprite);
	
//	void GameplayUpdate();
//	void GameplayRender();
//	void GameplayInput();
//	void GameplayOnExit();
//	void GameplayOnEnter();
//
//	void StartScreenUpdate();
//	void StartScreenRender();
//	void StartScreenInput();
//
//	void EndScreenUpdate();
//	void EndScreenRender();
//	void EndScreenInput();

//	static void DrawTextCentered(const char *text, int fontSize, Color color);
//	static void DrawTextCentered(const char *text, Vector2 offset, int fontSize, Color color);
//	static void DrawTextCenteredHorizontal(const char *text, int posY, int fontSize, Color color);

//	void SpawnAliens();
//	void cleanUpEntities();

//	void checkAllCollisions();

	Window window;
	Textures textures;
	Sounds sounds;
	Leaderboard leaderboard;
//
//	Player player;
//	std::vector<EnemyProjectile> EnemyProjectiles; //TODO: separate into PlayerProjectiles and EnemyProjectiles and get rid of EntityType
//	std::vector<PlayerProjectile> PlayerProjectiles; //TODO: separate into PlayerProjectiles and EnemyProjectiles and get rid of EntityType
//	std::vector<Wall> Walls;
//	std::vector<Alien> Aliens;
//	Background background;
//
//	std::vector<Sprite> sprites; //things to render, needed: texture, position, rect, hidden

	
	GameScene* _scene = nullptr;
//
//	Leaderboard leaderboard;
//	//TEXTBOX ENTER
//	char name[MAX_LETTER_COUNT + 1] = "\0";      //One extra space required for null terminator char '\0'
//	int letterCount = 0;
//
//	Rectangle textBox = { 600, 500, 225, 50 };
//	bool mouseOnText = false;
//
//	int framesCounter = 0;

};
