//
//  Entities.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef Entities_hpp
#define Entities_hpp
#include "Math.hpp"
#include "raylib.h"
#include "Constants.h"
#include <string>
#include <vector>

#include <expected>

enum struct ErrorType {
	MISSING_TEXTURE,
	MISSING_FILE,
};

class Entity {
protected:
	Vector2 position {0,0};
	Rectangle bounds {0,0, 100, 100};
	bool hidden = false;
public:
	bool isHidden() const noexcept { return hidden; }
	Rectangle getBounds() const noexcept { return bounds; }
	void setSize(float s) noexcept {bounds = ::getBounds(s); }

	void setPosition(const Vector2 &pos) noexcept { position = pos; }
	Vector2 getPosition() const noexcept { return position; }
	float getX() const noexcept { return position.x; }
	float getY() const noexcept { return position.y; }
};

class HealthObject {
public:
	HealthObject(int maxHealth = 1) : max_health(maxHealth) { setHealth(maxHealth); }

	void setHealth(int h) { health = clamp(h, 0, max_health); }
	void loseHealth(int h=1) { setHealth(getHealth() - h);}

	int getHealth() const noexcept { return health; }
	int getMaxHealth() const noexcept { return max_health; }
	bool isDead() const noexcept { return health < 1; }
protected:
	int max_health;
	int health = max_health;
};
class Sprite : public Entity {
public:
	Sprite(Texture2D* texture = nullptr) : Entity(), _texture(texture) { }
	Texture2D* _texture = nullptr;
	Rectangle getTextureRect() const noexcept { return texture_rect; }
	protected:
	Rectangle texture_rect = {0, 0, 100, 100};
};
class Player : public Sprite, public HealthObject {
public:
	Player();
	Player(std::vector<Texture2D>* textures);

	float getRadius() const noexcept { return PLAYER_RADIUS; }
	std::vector<Texture2D>* animation_textures;
	int activeTexture = 0;
	float animationTimer = 0;

	void Update();
	void Render();
	void Hit();
	void setX(float x) noexcept { position.x = clamp(x, PLAYER_RADIUS, WINDOW_WIDTH - PLAYER_RADIUS); }
	void moveX(float x) noexcept { setX(position.x + x); }

private:
	void animate();
};

class Projectile : public Sprite {
public:
	Projectile(const Vector2& pos, Texture2D *laserTexture = nullptr) : Sprite(laserTexture) { position = pos; setSize(PROJECTILE_SIZE); texture_rect = ::getBounds(PROJECTILE_TEXTURE_RESOLUTION); }
	int speed;
	LineSegment getLine() const noexcept { return LineSegment { position + Vector2{0, -PROJECTILE_LENGTH / 2}, position + Vector2{0, PROJECTILE_LENGTH / 2 } }; }
	int direction = 0;
	void Update();
	void Hit() { hidden = true;}
	virtual bool isEnemy() = 0;// {return false;}

};

class EnemyProjectile : public Projectile {
public:
	EnemyProjectile(Texture2D* laserTexture, const Vector2 &pos) : Projectile(pos, laserTexture) { direction = 1; position.y += 40; }

	virtual bool isEnemy() { return true; }
};

class PlayerProjectile : public Projectile {
public:
	PlayerProjectile(Texture2D* laserTexture, float x) : Projectile(Vector2(x,WINDOW_HEIGHT - PROJECTILE_START_Y), laserTexture) { direction = -1; }
	virtual bool isEnemy() { return false; }
};

class Wall : public Sprite, public HealthObject {
public:
	Wall(int index, Texture2D *barrierTexture);

	float getRadius() const noexcept { return WALL_RADIUS; }
	void Hit();
};

class Alien : public Sprite {
public:
	Alien(int col, int row, Texture2D *alienTexture); //position, scale, active, health, radius, update, render
	float getRadius() const noexcept { return  ALIEN_RADIUS; }
	bool moveRight = true;

	void Update();
	void Render();
	void Hit() { hidden = true; }
};


class Star : public Entity {
public:
	Star();

	float getSize() const noexcept { return size; }
//	void Render();
	float offsetX = 0;
private:
	float size = 1;
};


//
//class Background {
//public:
//	Background();
//	std::vector<Star> Stars;
//	float offset_x;
//
//	void Render();
//};


#endif /* Entities_hpp */
