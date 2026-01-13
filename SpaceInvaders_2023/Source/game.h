#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Assets.h"
#include "Window.hpp"
#include <string>
#include <vector>
#include <print>

#include "Player.h"
#include "Alien.h"
#include "Projectile.h"
#include "Bunker.h"
#include "Stars.h"

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};


struct PlayerData {
	std::string name;
	int score;
};

class Game {
	public:
	Game() : window(), renderer(window), player(&texturePack) {
		SetTargetFPS(FPS);
	}
	~Game() {}

	Window window;
	Renderer renderer;

	TexturePack texturePack;

	State gameState = State::STARTSCREEN;
	int score = 0;
	float alienShootTimer = 0;
	bool newHighScore = false;

	void Start();
	void SpawnWalls();
	void GameOver();

	void Continue();
	void Launch();

	void Update();
	void Render();

	void StartScreenUpdate();
	void StartScreenRender();
	void GameplayUpdate();
	void GameplayRender();
	void EndScreenUpdate();
	void EndScreenRender();

	void SpawnAliens();
	void UpdateBackground();
	void CheckCollisions();
	void MakeProjectile();
	void AlienShooting();
	void RemoveInactiveEntities();

	void UpdateStarPositions() { Star::offsetX = player.getPosition().x / -PARALLAX_FACTOR; }
//	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);
	bool CheckCollision(Rectangle rect1, Rectangle rect2) { return CheckCollisionRecs(rect1, rect2); }
	bool CheckCollision(Circle circle, Rectangle rect) { return CheckCollisionCircleRec(circle.center, circle.radius, rect);}
	bool CheckNewHighScore() { return (score > Leaderboard.back().score); }

	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();

	Player player;

	std::vector<Projectile> Projectiles;
	std::vector<Bunker> Bunkers;
	std::vector<Alien> Aliens;
	std::vector<Star> Stars;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };


	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};
