//
//  Entities.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#include "Entities.hpp"
#include "raylib.h"
#include <print>

void Player::Render(Texture2D texture) {
	//Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint
	DrawTexturePro(texture,
			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect),
			   NO_ROTATION,
			   NO_TINT);
}

void Player::hit() {
	lives -= 1;
	if(lives < 1) { //game over
	}
}

void Player::Update() {
	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT)) //interesting implementation...
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}
	
	position.x += PLAYER_SPEED * direction;
	
	if (getX() < 0 + PLAYER_RADIUS) //TODO: Clamp
	{
		position.x = 0 + PLAYER_RADIUS;
	}
	else if (getX() > WINDOW_WIDTH - PLAYER_RADIUS)
	{
		position.x = WINDOW_WIDTH - PLAYER_RADIUS;
	}
	
	
	//Determine frame for animation
	animationTimer += GetFrameTime();
	
	if (animationTimer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		animationTimer = 0;
	}
	else if (animationTimer > 0.4)
	{
		activeTexture++;
		animationTimer = 0;
	}
	
	
}


void Projectile::Update() {
	position.y += speed;
	
	// UPDATE LINE POSITION
	lineStart.y = position.y - PROJECTILE_LENGTH / 2; //TODO: these are tied to constants, use getter function
	lineEnd.y   = position.y + PROJECTILE_LENGTH / 2;		//getLineEnd() { Vector2 lineStart = position; lineStart.y -= 15; }
	
	lineStart.x = position.x;
	lineEnd.x   = position.x;
	
	if (position.y < 0 || position.y > PROJECTILE_BOUNDS ) { //Out of bounds (more magical numbers :D
		active = false;
	}
}

void Projectile::Render(Texture2D texture)
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
	DrawTexturePro(texture,
			   getBounds(PROJECTILE_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect), //origin
			   NO_ROTATION,
			   NO_TINT);
}


void Wall::Render(Texture2D texture)
{
	DrawTexturePro(texture,
			   getBounds(WALL_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect), //origin = dimensions / 2
			   NO_ROTATION,
			   NO_TINT);
	
	int textHalfWidth = MeasureText(TextFormat("%i", health), DEFAULT_FONT_SIZE) / 2;
	DrawText(TextFormat("%i", health), position.x-textHalfWidth, position.y+10, DEFAULT_FONT_SIZE, WALL_TEXT_COLOR);
	
}

Wall::Wall(int index) {
	position.y = WINDOW_HEIGHT - WALL_BASE_HEIGHT;
	position.x = (index + 1) * WINDOW_WIDTH / (WALL_COUNT + 1);
}

void Wall::Update() {
	// set walls as inactive when out of health
	// use setter instead of detecting health value
	if (health < 1)
	{
		active = false;
	}
}

Alien::Alien(int col, int row) {
	position.x = FORMATION_X + ALIEN_PADDING_X + (col * ALIEN_SPACING);
	position.y = FORMATION_Y + (row * ALIEN_SPACING);
	active = true;
	std::println("Alien Spawned, Row:{}, Column:{}, Position: {}", row, col, position);
}
void Alien::Update() {
	
	float direction = moveRight ? 1 : -1;
	if (moveRight)
	{
		position.x += ALIEN_SPEED * direction;
		
		if (position.x >= WINDOW_WIDTH) //touching right edge
		{
			moveRight = false; //moveRight is true, moveRight = false, moveRight = !moveRight;
			position.y += ALIEN_MOVEMENT_Y; //move down  //originally 50 but looks weird
		}
	}
	else
	{
		position.x += ALIEN_SPEED * direction;
		
		if (position.x <= 0) //touching left edge
		{
			moveRight = true; //moveRight is false, moveRight = true, moveRight = !moveRight;
			position.y += ALIEN_MOVEMENT_Y; //move down
		}
	}
}

void Alien::Render(Texture2D texture)
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);
	
	DrawTexturePro(texture,
			   getBounds(ALIEN_PLAYER_TEXTURE_RESOLUTION),
			   rect + position,
			   getCenter(rect),
			   NO_ROTATION,
			   NO_TINT);
}

Star::Star(const point& pos) : position(pos) {
	localPosition.x = GetRandomValue(-BACKGROUND_EDGE_SIZE, WINDOW_WIDTH + BACKGROUND_EDGE_SIZE);
	localPosition.y = GetRandomValue(0, WINDOW_HEIGHT);
	size = GetRandomValue(1, STAR_MAX_SIZE * 2) / 2;
}
//BACKGROUND
//void Star::Update() {
//	//position.x = position.x + localPosition.x;
//}

void Star::Render() {
	//DrawCircleV((int)position.x, (int)position.y, size, color);
	DrawCircleV(static_cast<Vector2>(position + localPosition), size, STAR_COLOR);
}


Background::Background() { //TODO: Star Constrcutor, and star count constant
	for (int i = 0; i < STAR_COUNT; i++) {
		Star newStar(position);
		Stars.push_back(newStar);
	}
}

void Background::setOffset(float offsetX) {
	position.x = offsetX;
	for(auto &star : Stars) {
		star.position.x = offsetX;
	}
}
//void Background::Update() {
//	for(auto &star : Stars) {
//		star.Update();
//	}
//}

void Background::Render() {
	for(auto &star : Stars) {
		star.Render();
	}
}



void Sprite::Render() {
	if(hidden || _texture == nullptr) return;
	DrawTexturePro(*_texture,
			   ::getBounds(_texture->width, _texture->height),
			   getBounds(),
			   getCenter(getBounds()), //origin
			   NO_ROTATION,
			   NO_TINT);
}
