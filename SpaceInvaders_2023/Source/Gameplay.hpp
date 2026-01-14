#pragma once
#include "GameScene.hpp"
#include "Alien.h"
#include "Player.h"
#include "Stars.h"
#include "Bunker.h"
#include "Projectile.h"

class EndScreen;

class Gameplay : public GameScene {
public:
	Gameplay(Game* game);
	~Gameplay() {}

	virtual std::optional<GameScene*> Update();
	virtual void Render(Renderer& renderer);

	EndScreen* GameOver() noexcept;

	void AliensShooting();
	void SpawnBunkers();
	void MakePlayerProjectile();
	void RemoveInactiveEntities();

	void CheckAllCollisions();
	bool DrawColliders(const Circle &circle, const Rectangle &rect, bool collision) {
		/*DrawRectangleLinesEx(rect, 5, collision ? GREEN : RED);
		 DrawCircleV(circle.center, circle.radius, collision ? GREEN : RED);*/
		return collision;
	}
	bool CheckCollision(Rectangle rect1, Rectangle rect2) { return CheckCollisionRecs(rect1, rect2); }
	bool CheckCollision(Circle circle, Rectangle rect) { return DrawColliders(circle, rect, CheckCollisionCircleRec(circle.center, circle.radius, rect)); }

	void CheckCollision(Alien& alien, Projectile& projectile);
	void CheckCollision(Player& alien, Projectile& projectile);
	void CheckCollision(Bunker& alien, Projectile& projectile);

	void setScore(int s) noexcept;
//	void setLivesText(int l) noexcept;
private:
	int score = 0;
	float alienShootTimer = 0;

	Player player;
	AlienSwarm alienSwarm;
	std::vector<Projectile> Projectiles;
	std::vector<Bunker> Bunkers;
	std::vector<Star> Stars;
	TextUI scoreText{"Score: 0", {50, 20}};
	TextUI livesText{"Lives: 3", {50, 70}};
};
