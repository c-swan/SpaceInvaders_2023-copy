//  Entities.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.

#ifndef Entities_hpp
#define Entities_hpp

#include "Math.hpp"
#include "raylib.h"
#include "Constants.h"
#include <string>
#include <vector>
#include <expected>

using texture_type = Texture2D*;

class Entity {
protected:
	Vector2 position {0,0};
	Rectangle bounds {0,0, 100, 100};
	bool hidden = false;
public:
	bool isHidden() const noexcept { return hidden; }
	void setSize(float s) noexcept { bounds = ::getBounds(s); }

	Rectangle getBounds() const noexcept { return bounds; }
	float getWidth() const noexcept { return bounds.width; }
	float getHeight() const noexcept { return bounds.height; }

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
	Sprite(texture_type texture) : Entity(), _texture(texture) { }
	texture_type _texture;
	Rectangle getTextureRect() const noexcept { return ::getBounds(_texture->width, _texture->height); }
	virtual void Update() {}
	virtual void Render() {
		if(hidden) return;
		DrawTexturePro(*_texture,
				   getTextureRect(),
				   bounds + position,
				   getCenter(bounds),
				   NO_ROTATION,
				   NO_TINT);
	}

};

class Player : public Sprite, public HealthObject {
public:
	Player(std::vector<Texture2D*> textures);

	float getRadius() const noexcept { return PLAYER_RADIUS; }
	Circle getCollider() noexcept { return Circle(position, getRadius()); }

	std::vector<Texture2D*> animation_textures;
	int activeTexture = 0;
	float animationTimer = 0;

	virtual void Update();

	void Hit();
	void setX(float x) noexcept { position.x = clamp(x, getRadius(), WINDOW_WIDTH - getRadius()); }
	void moveX(float x) noexcept { setX(position.x + x); }

private:
	void animate();
};

class Projectile : public Sprite {
public:
	Projectile(texture_type laserTexture, const Vector2& pos) : Sprite(laserTexture) { setPosition(pos); setSize(PROJECTILE_SIZE); }
	int speed;
	LineSegment getLine() const noexcept { return LineSegment { position + Vector2{0, -PROJECTILE_LENGTH / 2}, position + Vector2{0, PROJECTILE_LENGTH / 2 } }; }
	LineSegment getCollider() const noexcept { return getLine(); }
	int direction = 0;
	virtual void Update();
	void Hit() { hidden = true;}
	virtual bool isEnemy() = 0;// {return false;}

};

class EnemyProjectile : public Projectile {
public:
	EnemyProjectile(texture_type laserTexture, const Vector2 &pos) : Projectile(laserTexture, pos) { direction = 1; position.y += 40; }

	virtual bool isEnemy() { return true; }
};

class PlayerProjectile : public Projectile {
public:
	PlayerProjectile(texture_type laserTexture, float x) : Projectile(laserTexture, Vector2(x,WINDOW_HEIGHT - PROJECTILE_START_Y)) { direction = -1; }
	virtual bool isEnemy() { return false; }
};

class Wall : public Sprite, public HealthObject {
public:
	Wall(int index, texture_type barrierTexture);

	virtual void Update() {}
	virtual void Render();
	float getRadius() const noexcept { return WALL_RADIUS; }
	Circle getCollider() const noexcept { return Circle(position, getRadius());}
	void Hit();
};

class Alien : public Sprite {
public:
	Alien(int col, int row, texture_type alienTexture); //position, scale, active, health, radius, update, render
	float getRadius() const noexcept { return  ALIEN_RADIUS; }
	Circle getCollider() const noexcept { return Circle(position, getRadius());}

	virtual void Update();
	void Hit() { hidden = true; }
	private:
	bool moveRight = true;

};


class Star : public Entity {
public:
	Star();

	virtual void setSize(float s) { Entity::setSize(size = s); }
	void Render() { DrawCircleV(position + Vector2(star_offset_x, 0), getSize(), STAR_COLOR); }
	float getSize() const noexcept { return size; }
	static float star_offset_x;
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
