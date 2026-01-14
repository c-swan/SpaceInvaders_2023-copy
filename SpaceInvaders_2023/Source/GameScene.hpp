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
	virtual void Render(Renderer& renderer) = 0;
};

class EndScreen;

class Gameplay : public GameScene {
public:
	Gameplay(Game* game);
	~Gameplay() {}

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	void Pause() noexcept {paused = !paused; } //new functionality (Gameplay)
	EndScreen* GameOver() noexcept;
	std::nullopt_t Continue() const noexcept { return std::nullopt; }

	bool paused = false;
	int score = 0;
	float alienShootTimer = 0; //Aliens shooting

	//	std::optional<GameScene*> UpdateAliens();
	void AliensShooting();
	void SpawnAliens();
	void SpawnBunkers();
	void MakeProjectile();
	void RemoveInactiveEntities();
	void UpdateStarPositions() { Star::offsetX = player.getPosition().x / -PARALLAX_FACTOR; }

	void CheckAllCollisions();
	bool DrawColliders(const Circle &circle, const Rectangle &rect, bool collision) {
		DrawRectangleLinesEx(rect, 5, collision ? GREEN : RED);
		DrawCircleV(circle.center, circle.radius, collision ? GREEN : RED);
		return collision;
	}
	bool CheckCollision(Rectangle rect1, Rectangle rect2) { return CheckCollisionRecs(rect1, rect2); }
	bool CheckCollision(Circle circle, Rectangle rect) { return DrawColliders(circle, rect, CheckCollisionCircleRec(circle.center, circle.radius, rect)); }
	
	void CheckCollision(Alien& alien, Projectile& projectile);
	void CheckCollision(Player& alien, Projectile& projectile);
	void CheckCollision(Bunker& alien, Projectile& projectile);
//	bool CheckNewHighScore() { return (score > Leaderboard.back().score); }

	Player player;
//	std::vector<Alien> Aliens;
	AlienSwarm alienSwarm;
	std::vector<Projectile> Projectiles;
	std::vector<Bunker> Bunkers;
	std::vector<Star> Stars;
	TextUI scoreText;
	TextUI livesText;
};

class StartScreen : public GameScene {
public:
	StartScreen(Game* game) : GameScene(game) {
		text.emplace_back(TextUI("SPACE INVADERS", {200, 100}, TITLE_FONT_SIZE));
		text.emplace_back(TextUI("PRESS SPACE TO BEGIN", {200, 350}));
	}
	~StartScreen() { }

	std::vector<TextUI> text;

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);
	Gameplay* StartGame() { return new Gameplay(_game); }
};

class EndScreen : public GameScene {
public:
	//	EndScreen(Game* game) : GameScene(game) {}
	EndScreen(Game* game, int s);
	~EndScreen();

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	void RenderNewHighscore(Renderer& renderer);
	void ShowScoreboard(Renderer& renderer);

private:
	bool newHighscore = false;
	int score = 0;
	int highscore = 0;

	char name[MAX_LETTER_COUNT + 1] = "\0";
	int letterCount = 0;

	Rectangle textBoxBounds = { 600, 450, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;
};
