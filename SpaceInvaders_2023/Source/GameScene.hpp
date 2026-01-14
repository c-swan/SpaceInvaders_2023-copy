#pragma once
#include <raylib.h>

#include "Player.h"
#include "Projectile.h"
#include "Alien.h"
#include "Bunker.h"
#include "Stars.h"

#include <optional>
#include <vector>
#include <string>

#include "Constants.h"
#include "TextUI.h"

class Game;

class GameScene {
public:
	GameScene(Game* game = nullptr) : _game(game) {}
	virtual ~GameScene() {}

	Game* _game = nullptr;
	virtual std::optional<GameScene*> Update() = 0;
	virtual void Render() = 0;
};

class EndScreen;

class Gameplay : public GameScene {
public:
	Gameplay(Game* game);
	~Gameplay();

	virtual std::optional<GameScene*> Update();
	virtual void Render();

	void Pause() noexcept {paused = !paused; } //new functionality (Gameplay)
	EndScreen* GameOver() noexcept;
	std::nullopt_t Continue() const noexcept { return std::nullopt; }

	bool paused = false;
	int score = 0;
	float shootTimer = 0; //Aliens shooting

	//	std::optional<GameScene*> UpdateAliens();
	void AliensShooting();
	void CleanUpEntities();
	void SpawnAliens();

	void CheckAllCollisions();
	bool CheckCollision(Rectangle rect1, Rectangle rect2) { return CheckCollisionRecs(rect1, rect2); }
	bool CheckCollision(Circle circle, Rectangle rect) { return DrawColliders(circle, rect, CheckCollisionCircleRec(circle.center, circle.radius, rect)); }
	bool CheckNewHighScore() { return (score > Leaderboard.back().score); }

	Player player;
	std::vector<Alien> Aliens;
	std::vector<Projectile> Projectiles;
	std::vector<Bunker> Bunkers;
	std::vector<Star> Stars;
};

class StartScreen : public GameScene {
public:
	StartScreen(Game* game) : GameScene(game), text{ TextUI("SPACE INVADERS", {200, 100 }, TITLE_FONT_SIZE), TextUI("PRESS SPACE TO BEGIN", {200, 350})} {
	}
	~StartScreen() {}

	std::vector<TextUI> text;

	virtual std::optional<GameScene*> Update();
	virtual void Render();
	Gameplay* StartGame() { return new Gameplay(_game); }
};

class EndScreen : public GameScene {
public:
	//	EndScreen(Game* game) : GameScene(game) {}
	EndScreen(Game* game, int s); //new highscore
	~EndScreen();

	virtual std::optional<GameScene*> Update();
	virtual void Render();

	void ShowScoreboard();
	void DrawInputCursor();
	void DrawInputBox();

private:
	bool newHighScore = false;
	int score = 0;
	int highscore = 0;

	char name[MAX_LETTER_COUNT + 1] = "\0";
	int letterCount = 0;

	Rectangle textBoxBounds = { 600, 450, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;
};
