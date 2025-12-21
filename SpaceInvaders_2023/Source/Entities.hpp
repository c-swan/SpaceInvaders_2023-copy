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
enum struct ProjectileType //TODO: EntityType only used to distinguish projectiles, use derived classes instead
{
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

class Sprite {
public:
	Sprite(Texture2D* texture) : _texture(texture) {}
	Texture2D* _texture = nullptr;

	point position{0,0};
	scale scale{1,1};
	bool hidden = false;

	inline Rectangle getBounds() { return Rectangle{position.x, position.y, scale.width, scale.height}; }
	inline Vector2 getOrigin() { return getCenter(getBounds()); }
	void Render();
};

class Player {
public:
	explicit Player() : position(point(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT)) {}

	point position;
	Rectangle rect {0, 0, PLAYER_SIZE, PLAYER_SIZE};
//	const float radius = PLAYER_RADIUS;

	float getX() const noexcept { return position.x; }
	float getY() const noexcept { return position.y; }
	//	float speed = 7; //TODO: constant...

	int lives = MAX_LIVES; //TODO: initial value constant

	int direction = 0; //velocity direction x-axis, 0, +1 or -1
	int activeTexture = 0; //texture number...
	float animationTimer = 0; //timer for what?

	void Update();
	void Render(Texture2D texture); //TODO: pass by const ref

	void hit();
};

class Projectile {
public:
	Projectile(const point& pos) : position(pos) {}

	point position = {0,0};
	Rectangle rect{0, 0, PROJECTILE_SIZE, PROJECTILE_SIZE};
	int speed;
	bool active = true;

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 }; //what is this line...?
	Vector2 lineEnd = { 0, 0 };

	void Update();
	void Render(Texture2D texture);

	virtual bool isEnemy() = 0;// {return false;}
};

class EnemyProjectile : public Projectile {
public:
	EnemyProjectile(const point &pos) : Projectile(pos) { speed = PROJECTILE_SPEED; position.y += 40; }
	virtual bool isEnemy() { return true; }
};

class PlayerProjectile : public Projectile {
public:
	PlayerProjectile(const point &pos) : Projectile(pos) { speed = -PROJECTILE_SPEED; }
	virtual bool isEnemy() { return false; }
};

struct Wall {
public:
	explicit Wall(int index);

	point position {0, 0};
	Rectangle rect {0, 0, WALL_SIZE, WALL_SIZE };
	bool active = true;

	//const int radius = WALL_RADIUS;

	int health = WALL_MAX_HEALTH;

	void Update();
	void Render(Texture2D texture);
};

struct Alien {
public:
	Alien(int col, int row); //position, scale, active, health, radius, update, render

	point position{0,0};
	Rectangle rect {0, 0, ALIEN_SIZE, ALIEN_SIZE};
	bool active = true;

//	const int radius = ALIEN_RADIUS;

	bool moveRight = true;

	void Update();
	void Render(Texture2D texture);
};


struct Star {
	explicit Star();
	explicit Star(const point &pos);

	point localPosition = { 0, 0 }; //local position for child,
	point position = { 0, 0 }; //parent position + local position
					   //	Color color = STAR_COLOR; //constant?
	float size = 1;

	//	void Update();
	void Render();
};

class Background {
public:
	explicit Background();
	std::vector<Star> Stars;
	point position = {0,0}; //replaces offset

	//	void Initialize(); //TODO: use constructor
	//	void Update();
	void Render();

	void setOffset(float offsetX);
};


#endif /* Entities_hpp */
