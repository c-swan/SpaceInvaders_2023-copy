//
//  Entities.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#include "Entities.hpp"
#include "raylib.h"
#include <print>
#include <cstdlib>
#include <algorithm>
#include "Math.hpp"
#include <cassert>

Player::Player(std::vector<Texture2D>* textures) : Sprite() , HealthObject(PLAYER_MAX_HEALTH), animation_textures(textures) {
	position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT};
	setSize(PLAYER_SIZE);
	texture_rect = ::getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION);
	if(animation_textures == nullptr) return;
	if(animation_textures->empty()) return;

	_texture = &animation_textures->front();
}

void Player::Hit() {
	loseHealth();
	if(isDead()) hidden = true;
}

void Player::Update() {

	int direction = 0;
	if (IsKeyDown(KEY_LEFT))  {
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		direction++;
	}
	
	moveX(PLAYER_SPEED * direction);

//	if (getX() < PLAYER_RADIUS) { //TODO: Clamp
//		setX(PLAYER_RADIUS);
//	}
//	if (getX() > WINDOW_WIDTH - PLAYER_RADIUS) {
//		position.x = WINDOW_WIDTH - PLAYER_RADIUS;
//	}
//
	animate();
}


void Player::animate() {
	assert(animation_textures != nullptr);
	animationTimer += GetFrameTime();

	if(animationTimer <= SHIP_ANIMATION_TIME) return;

	(++activeTexture) %= (animation_textures->size());	//	activeTexture++; activeTexture %= 2; //wrap around
	_texture = &(*animation_textures)[activeTexture];
	animationTimer = 0;
}

void Projectile::Update() {
	if(hidden) return;
	position.y += PROJECTILE_SPEED * direction;
	if(!floatInRange(getY(), 0, PROJECTILE_BOUNDS)) hidden = true; //Out of bounds (more magical numbers :D
}


Wall::Wall(int index, Texture2D *barrierTexture = nullptr) : Sprite(barrierTexture), HealthObject(WALL_MAX_HEALTH) {
	position.y = WINDOW_HEIGHT - WALL_BASE_HEIGHT;
	position.x = (index + 1) * WINDOW_WIDTH / (WALL_COUNT + 1);
	texture_rect = ::getBounds(WALL_TEXTURE_RESOLUTION);
	setSize(WALL_SIZE);
}

void Wall::Hit() {
	loseHealth();
	if(isDead()) { hidden = true; }
}

Alien::Alien(int col, int row, Texture2D *alienTexture = nullptr) : Sprite(alienTexture) {
	position.x = FORMATION_X + ALIEN_PADDING_X + (col * ALIEN_SPACING);
	position.y = FORMATION_Y + (row * ALIEN_SPACING);
	texture_rect = ::getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION);
	setSize(ALIEN_SIZE);
}
void Alien::Update() {
	position.x += ALIEN_SPEED * (moveRight ? 1 : -1);
	if ((moveRight && position.x >= WINDOW_WIDTH) || (!moveRight && (position.x <= 0)))
	{
		moveRight = !moveRight;
		position.y += ALIEN_MOVEMENT_Y;
	}
}

Star::Star() {
	position.x = GetRandomValue(-BACKGROUND_EDGE_SIZE, WINDOW_WIDTH + BACKGROUND_EDGE_SIZE);
	position.y = GetRandomValue(0, WINDOW_HEIGHT);
	size = GetRandomValue(1, STAR_MAX_SIZE * 2) / 2;
	setSize(size);
}
