//
//  Aliens.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-28.
//

#ifndef Aliens_hpp
#define Aliens_hpp
#include "Entities.hpp"
#include <vector>

class Alien : public Sprite {
public:
	Alien(int row, int col, texture_type alienTexture); //position, scale, active, health, radius, update, render
	float getRadius() const noexcept { return  ALIEN_RADIUS; }
	Circle getCollider() const noexcept { return Circle(getPosition(), getRadius());}
	void moveX(float x) noexcept { position.x += x; }
	void moveDown() noexcept { position.y += ALIEN_MOVEMENT_Y; }
	bool isOutOfBounds() const noexcept { return !floatInRange(getX(), 0, WINDOW_WIDTH); }
	void Hit() { hidden = true; }

	virtual void Update();
};

class AlienSwarm {
public:
	AlienSwarm(Texture2D* alienTexure) : _texture(alienTexure) {}
	~AlienSwarm() { aliens.clear(); }
	void Update();
	void Render() { for(auto& alien : aliens) { alien.Render(); }}
	void SpawnAliens();

	AlienSwarm(const AlienSwarm&) = delete;
	AlienSwarm(AlienSwarm&&) = delete;
	AlienSwarm& operator=(const AlienSwarm&) = delete;
	AlienSwarm& operator=(AlienSwarm&) = delete;

private:

	std::vector<Alien> aliens;
	bool moveRight = true;
	Texture2D* _texture = nullptr;
};

#endif /* Aliens_hpp */
