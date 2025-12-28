//
//  Entities.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//
#include "Entities.hpp"
#include "raylib.h"
#include <cstdlib>
#include <algorithm>
#include "Math.hpp"
#include <cassert>
#include "Render.h"

Player::Player(std::vector<Texture2D*> textures) : Sprite(textures.front()), HealthObject(PLAYER_MAX_HEALTH), animation_textures(textures) {
	position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT};
	setSize(PLAYER_SIZE);
	assert(!animation_textures.empty());
}

void Player::Hit() {
	if(isHidden()) return;
	loseHealth();
	if(isDead()) hidden = true;
}

void Player::Update() {
	if(isHidden()) return;
	int direction = 0;
	if (IsKeyDown(KEY_LEFT))  { direction--; }
	if (IsKeyDown(KEY_RIGHT)) { direction++; }

	moveX(PLAYER_SPEED * direction);
	animate();
}


void Player::animate() {
	animationTimer += GetFrameTime();

	if(animationTimer <= SHIP_ANIMATION_TIME) return;

	(++activeTexture) %= animation_textures.size();	//	activeTexture++; activeTexture %= 2; //wrap around
	_texture = (animation_textures)[activeTexture];
	animationTimer = 0;
}

void Projectile::Update() {
	if(isHidden()) return;
	position.y += PROJECTILE_SPEED * direction;
	if(isOutOfBounds()) hidden = true; //Out of bounds
}


Wall::Wall(int index, texture_type barrierTexture) : Sprite(barrierTexture), HealthObject(WALL_MAX_HEALTH) {
	position.y = WINDOW_HEIGHT - WALL_BASE_HEIGHT;
	position.x = (index + 1) * WINDOW_WIDTH / (WALL_COUNT + 1);
	setSize(WALL_SIZE);
}

void Wall::Hit() {
	if(isHidden()) return;
	loseHealth();
	if(isDead()) hidden = true;
}

void Wall::Render() {
	if(isHidden()) return;
	Sprite::Render();
	Render::DrawTextCentered(std::to_string(getHealth()), textPosition + position, DEFAULT_FONT_SIZE, WALL_TEXT_COLOR);
}

Alien::Alien(int col, int row, texture_type alienTexture) : Sprite(alienTexture) {
	position.x = FORMATION_X + ALIEN_PADDING_X + (col * ALIEN_SPACING);
	position.y = FORMATION_Y + (row * ALIEN_SPACING);
	setSize(ALIEN_SIZE);
}
void Alien::Update() {
	position.x += ALIEN_SPEED * (moveRight ? 1 : -1);
	if (floatInRange(getX(), 0, WINDOW_WIDTH)) return;

	moveRight = !moveRight;
	position.y += ALIEN_MOVEMENT_Y;
}

Star::Star() {
	position.x = GetRandomValue(-BACKGROUND_EDGE_SIZE, WINDOW_WIDTH + BACKGROUND_EDGE_SIZE);
	position.y = GetRandomValue(0, WINDOW_HEIGHT);
	setSize(GetRandomValue(1, STAR_MAX_SIZE * 2) / 2);
}


