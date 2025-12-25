//
//  GameScene.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef GameScene_hpp
#define GameScene_hpp
#include "Entities.hpp"
#include <string>
#include <vector>
#include "Textures.hpp"
#include "Leaderboard.hpp"

class Game;

class GameScene {
public:
	GameScene(Game* game = nullptr) : _game(game) {}
	virtual ~GameScene() {}

//	virtual void OnEnter() = 0;
//	virtual void OnExit() = 0;
	Game* _game = nullptr;

	virtual std::optional<GameScene*> Update() = 0;
	virtual void Render() = 0;


};

class Gameplay : public GameScene {
public:
	Gameplay(Game* game);
	~Gameplay();


	virtual std::optional<GameScene*> Update();
	virtual void Render();
	void Render(const Sprite& sprite);
	void Pause() noexcept {paused = !paused; } //new functionality (Gameplay)

	bool paused = false;
	int score = 0;
	float shootTimer = 0; //Aliens shooting

	void RenderWallText(const Wall& wall);
	void AliensShooting();
	void CleanUpEntities();
	void SpawnAliens();
	void CheckAllCollisions();

	Player player;
	std::vector<Sprite> Sprites; //for rendering
	std::vector<EnemyProjectile> EnemyProjectiles;
	std::vector<PlayerProjectile> PlayerProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<Star> Stars;
	float star_offset_x = 0;

};

class StartScreen : public GameScene {
public:
	StartScreen(Game* game = nullptr);
	~StartScreen();

	virtual std::optional<GameScene*> Update();
	virtual void Render();
};

class EndScreen : public GameScene {
public:
	EndScreen();
	EndScreen(Game* game, int s); //new highscore
	~EndScreen();

	virtual std::optional<GameScene*> Update();
	virtual void Render();

private:
	bool newHighScore = false;
	int score = 0;
	int highscore = 0;

	char name[MAX_LETTER_COUNT + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;
};

#endif /* GameScene_hpp */
