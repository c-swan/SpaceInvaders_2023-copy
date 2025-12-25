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
	Rectangle getBounds() const noexcept {return bounds; }
	void setSize(float s) noexcept {bounds = {0,0, s, s}; }
	void setPosition(const Vector2 &pos) noexcept { position = pos; }
	Vector2 getPosition() const noexcept { return position; }
	float getX() const noexcept { return position.x; }
	float getY() const noexcept { return position.y; }
};
class Sprite : public Entity {
public:
	Sprite(Texture2D* texture = nullptr) : Entity(), _texture(texture) { }
	Texture2D* _texture = nullptr;
	Rectangle getTextureRect() const noexcept { return texture_rect; }
	protected:
	Rectangle texture_rect = {0, 0, 100, 100};
};
class Player : public Sprite {
public:
	Player(Texture2D* texture = nullptr) : Sprite(texture) { position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT}; setSize(PLAYER_SIZE); texture_rect = ::getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION);}

	int lives = MAX_LIVES; //TODO: initial value constant

	int activeTexture = 0; //texture number...
	float animationTimer = 0; //timer for what?

	void Update();
	void Render();
	void Hit();
	bool isDead() const noexcept { return lives < 1; }

private:
	void animate();
};

class Projectile : public Sprite {
public:
	Projectile(const Vector2& pos, Texture2D *laserTexture = nullptr) : Sprite(laserTexture) { position = pos; setSize(PROJECTILE_SIZE); texture_rect = ::getBounds(PROJECTILE_TEXTURE_RESOLUTION); }
	int speed;
	LineSegment getLine() const noexcept { return LineSegment { position + Vector2{0, -PROJECTILE_LENGTH / 2}, position + Vector2{0, PROJECTILE_LENGTH / 2 } }; }

	void Update();
//	void Render(Texture2D texture);
	void Hit() { hidden = true;}

	virtual bool isEnemy() = 0;// {return false;}

};

class EnemyProjectile : public Projectile {
public:
	EnemyProjectile(Texture2D* laserTexture, const Vector2 &pos) : Projectile(pos, laserTexture) { speed = PROJECTILE_SPEED; position.y += 40; }
	virtual bool isEnemy() { return true; }
};

class PlayerProjectile : public Projectile {
public:
	PlayerProjectile(Texture2D* laserTexture, const Vector2 &pos) : Projectile(pos, laserTexture) { speed = -PROJECTILE_SPEED; }
	virtual bool isEnemy() { return false; }
};

class Wall : public Sprite {
public:
	Wall(int index, Texture2D *barrierTexture);

//	Vector2 position {0, 0};
//	Rectangle rect {0, 0, WALL_SIZE, WALL_SIZE };
//	bool active = true;


	//const int radius = WALL_RADIUS;

//	void Update();
	void Hit();
	int getHealth() const noexcept { return health; }
	private:
	int health = WALL_MAX_HEALTH;

};

class Alien : public Sprite {
public:
	Alien(int col, int row, Texture2D *alienTexture); //position, scale, active, health, radius, update, render

//	Vector2 position{0,0};
//	Rectangle rect {0, 0, ALIEN_SIZE, ALIEN_SIZE};
//	bool active = true;

//	const int radius = ALIEN_RADIUS;

	bool moveRight = true;

	void Update();
	void Render();
	void Hit() { hidden = true; }
};


class Star : public Entity {
public:
	Star();

	float getSize() const noexcept { return size; }
	void Render();
private:
	float size =1;
};

class Background {
public:
	Background();
	std::vector<Star> Stars;
	float offset_x;

	void Render();
};


#endif /* Entities_hpp */
