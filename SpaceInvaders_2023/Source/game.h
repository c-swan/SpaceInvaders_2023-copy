#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include <map>
#include "GameState.hpp"
#include "Entities.hpp"
#include "Constants.h"
//TODO: why are there like 10 structs defined in one file???

class Game
{
	public:
	Game() { setState(StartScreen::getInstance()); }


	void setState(GameState& gameState);
	GameState* getState() const noexcept { return currentState; }

	private:
	GameState* currentState;

	public:
	// Score
	int score;

	//Aliens shooting
	float shootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 };  //how about default constructor?

	int formationWidth = 8; //how about constant?
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;

	void Start();
	void End();

	void Continue();
	void Launch();

	void Update();
	void Render();

	void SpawnAliens();
	void checkCollisions();
	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);
	bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();


	// Entity Storage and Resources
	Resources resources;
	Player player;

	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::map<std::string, int> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	Background background;


	Vector2 playerPos; //maybe put this in the entity? lol
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
