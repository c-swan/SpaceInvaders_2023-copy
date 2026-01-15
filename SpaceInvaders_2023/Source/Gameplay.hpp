#pragma once
#include "GameScene.hpp"
#include "Alien.hpp"
#include "Player.hpp"
#include "Stars.hpp"
#include "Bunker.hpp"
#include "Projectile.hpp"

class EndScreen;

class Gameplay : public GameScene {
public:
	Gameplay(Game* game);
	~Gameplay() = default;

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	EndScreen* GameOver() noexcept;

private:
	int score = 0;
	float alien_shoot_timer = 0;

	Player player;
	AlienSwarm alienSwarm;

	std::vector<Projectile> Projectiles;
	std::vector<Bunker> Bunkers;
	std::vector<Star> Stars;

	TextUI scoreText{"Score: 0", {LEFT_MARGIN, 20}};
	TextUI livesText{"Lives: 3", {LEFT_MARGIN, 70}};

	void AliensShooting();
	void SpawnBunkers();
	void MakePlayerProjectile();
	void RemoveInactiveEntities();

	void CheckAllCollisions();
	void CheckCollision(Alien& alien, Projectile& projectile);
	void CheckCollision(Player& alien, Projectile& projectile);
	void CheckCollision(Bunker& alien, Projectile& projectile);

	bool DrawColliders(const Circle &circle, const Rectangle &rect, bool collision);
	bool CheckCollision(Rectangle rect1, Rectangle rect2);
	bool CheckCollision(Circle circle, Rectangle rect);
	bool CheckCollisionDebug(Circle circle, Rectangle rect);


	void setScore(int s) noexcept;
};
