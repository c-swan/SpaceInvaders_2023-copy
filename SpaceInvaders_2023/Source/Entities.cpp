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

//void Player::Render(Texture2D texture) {
//	//Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint
//	DrawTexturePro(texture,
//			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
//			   rect + position,
//			   getCenter(rect),
//			   NO_ROTATION,
//			   NO_TINT);
//}
Player::Player() : Sprite() {
	position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT};
	setSize(PLAYER_SIZE); texture_rect = ::getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION);
}
Player::Player(std::vector<Texture2D>* textures) : Sprite(), animation_textures(textures) {
	Player();
	if(animation_textures == nullptr) return;
	if(animation_textures->empty()) return;

	_texture = &animation_textures->front();
}

void Player::Hit() {
	lives--;
	if (lives < 1) lives = 0;
	hidden = true;
}

void Player::setX(float x) noexcept {
	position.x = clamp(static_cast<int>(x), PLAYER_RADIUS, WINDOW_WIDTH - PLAYER_RADIUS);
	if (x < PLAYER_RADIUS) { //TODO: Clamp
		position.x = PLAYER_RADIUS;
	}
	else if (x > WINDOW_WIDTH - PLAYER_RADIUS) {
		position.x = WINDOW_WIDTH - PLAYER_RADIUS;
	}
	else {
		position.x = x;
	}
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

	if (getX() < PLAYER_RADIUS) { //TODO: Clamp
		setX(PLAYER_RADIUS);
	}
	if (getX() > WINDOW_WIDTH - PLAYER_RADIUS) {
		position.x = WINDOW_WIDTH - PLAYER_RADIUS;
	}

	animate();
}


void Player::animate() {
	animationTimer += GetFrameTime();

	if(animationTimer <= SHIP_ANIMATION_TIME) return;

	(++activeTexture) %= 2;	//	activeTexture++; activeTexture %= 2; //wrap around
	animationTimer = 0;
}
void Projectile::Update() {
	if(hidden) return;
	position.y += PROJECTILE_SPEED * direction;
	if(floatInRange(getY(), 0, PROJECTILE_BOUNDS )) return; //Out of bounds (more magical numbers :D
   hidden = true;
}

//
//void Projectile::Render(Texture2D texture)
//{
//	//DrawCircle((int)position.x, (int)position.y, 10, RED);
//	DrawTexturePro(texture,
//			   getBounds(PROJECTILE_TEXTURE_RESOLUTION),
//			   bounds + position,
//			   getCenter(rect), //origin
//			   NO_ROTATION,
//			   NO_TINT);
//}



//void Wall::Render(Texture2D texture)
//{
//	DrawTexturePro(texture,
//			   getBounds(WALL_TEXTURE_RESOLUTION),
//			   rect + position,
//			   getCenter(rect), //origin = dimensions / 2
//			   NO_ROTATION,
//			   NO_TINT);
//	
//	int textHalfWidth = MeasureText(TextFormat("%i", health), DEFAULT_FONT_SIZE) / 2;
//	DrawText(TextFormat("%i", health), position.x-textHalfWidth, position.y+10, DEFAULT_FONT_SIZE, WALL_TEXT_COLOR);
//	
//}

Wall::Wall(int index, Texture2D *barrierTexture = nullptr) : Sprite(barrierTexture) {
	position.y = WINDOW_HEIGHT - WALL_BASE_HEIGHT;
	position.x = (index + 1) * WINDOW_WIDTH / (WALL_COUNT + 1);
//	_texture = barrierTexture;
	texture_rect = ::getBounds(WALL_TEXTURE_RESOLUTION);
	setSize(WALL_SIZE);
}
//
//void Wall::Update() {
//	if (health < 1) {
//		hidden = true;
//	}
//}


void Wall::Hit() {
	health--;
	if(isDead()) { health = 0; hidden = true; }
}

Alien::Alien(int col, int row, Texture2D *alienTexture = nullptr) : Sprite(alienTexture) {
	position.x = FORMATION_X + ALIEN_PADDING_X + (col * ALIEN_SPACING);
	position.y = FORMATION_Y + (row * ALIEN_SPACING);
	_texture = alienTexture;
	texture_rect = ::getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION);
	setSize(ALIEN_SIZE);
	hidden = false;
	//std::println("Alien Spawned, Row:{}, Column:{}, Position: {}", row, col, position);
}
void Alien::Update() {
	//	float direction = moveRight ? 1 : -1;
	position.x += ALIEN_SPEED * (moveRight ? 1 : -1);
	if ((moveRight && position.x >= WINDOW_WIDTH) || (!moveRight && (position.x <= 0))) {
		moveRight = !moveRight;
		position.y += ALIEN_MOVEMENT_Y;
	}
//	else {
//		if (position.x <= 0)
//		{
//			moveRight = !moveRight;
//			position.y += 50;
//		}
//	}
}
//
//void Alien::Render(Texture2D texture)
//{
//	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
//	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);
//	
//	DrawTexturePro(texture,
//			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
//			   rect + position,
//			   getCenter(rect),
//			   NO_ROTATION,
//			   NO_TINT);
//}

Star::Star() {
	position.x = GetRandomValue(-BACKGROUND_EDGE_SIZE, WINDOW_WIDTH + BACKGROUND_EDGE_SIZE);
	position.y = GetRandomValue(0, WINDOW_HEIGHT);
	size = GetRandomValue(1, STAR_MAX_SIZE * 2) / 2;
	setSize(size);
}
//BACKGROUND
//void Star::Update() {
//	//position.x = position.x + localPosition.x;
//}


//Background::Background() {
//	for (int i = 0; i < STAR_COUNT; i++) {
//		Star newStar;
//		Stars.push_back(newStar);
//	}
//}

//void Background::Render() {
//	for(auto &star : Stars) {
//		DrawCircleV(star.getPosition() + Vector2(offset_x, 0), star.getSize(), STAR_COLOR);
//	}
//}
///

