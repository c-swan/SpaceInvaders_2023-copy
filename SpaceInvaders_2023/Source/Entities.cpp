//
//  Entities.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#include "Entities.hpp"
#include "Constants.h"
#include <print>

Player::Player() {
	//Move to constructor??
	float window_width = static_cast<float>(GetScreenWidth());
	int window_height = GetScreenHeight();

	position.x = window_width / 2;
	position.y = window_height - PLAYER_BASE_HEIGHT;
	std::println("Player Position: ", position.x, position.y);
}

void Player::Update()
{

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += PLAYER_SPEED * direction;

	if (position.x < 0 + radius)
	{
		position.x = 0 + radius;
	}
	else if (position.x > GetScreenWidth() - radius)
	{
		position.x = GetScreenWidth() - radius;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}


}

void Player::Render(Texture2D texture)
{
	float window_height = GetScreenHeight();

	DrawTexturePro(texture,
			   {
		0,
		0,
		352,
		352,
	},
			   {
		position.x, window_height - player_base_height,
		100,
		100,
	}, { 50, 50 },
			   0,
			   WHITE);
}


Projectile::Projectile(Vector2& pos, EntityType et) {
	position = pos;
	position.y += 40; //offset
	type = et;
	//type = EntityType::ENEMY_PROJECTILE; //....
}
void Projectile::Update()
{
	position.y -= PROJECTILE_SPEED;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y   = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x   = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(Texture2D texture)
{
	//DrawCircle((int)position.x, (int)position.y, 10, RED);
	DrawTexturePro(texture,
			   {
		0,
		0,
		176,
		176,
	},
			   {
		position.x,
		position.y,
		50,
		50,
	}, { 25 , 25 },
			   0,
			   WHITE);
}

void Wall::Render(Texture2D texture)
{
	DrawTexturePro(texture,
			   {
		0,
		0,
		704,
		704,
	},
			   {
		position.x,
		position.y,
		200,
		200,
	}, { 100 , 100 },
			   0,
			   WHITE);


	DrawText(TextFormat("%i", health), position.x-21, position.y+10, 40, RED);

}

void Wall::Update() {
	// set walls as inactive when out of health
	if (health < 1) {
		active = false;
	}


}

void Alien::Update()
{
	int window_width = GetScreenWidth();
//difference is direction and if to flip at 0 or window_width
	if (moveRight)
	{
		position.x += ALIEN_SPEED;

		if (position.x >= window_width) //why are we calling this again after getting the var window_width????
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= ALIEN_SPEED;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(Texture2D texture)
{
	//DrawRectangle((int)position.x - 25, (int)position.y, 30, 30, RED);
	//DrawCircle((int)position.x, (int)position.y, radius, GREEN);



	DrawTexturePro(texture,
			   {
		0,
		0,
		352,
		352,
	},
			   {
		position.x,
		position.y,
		100,
		100,
	}, {50 , 50},
			   0,
			   WHITE);
}



//BACKGROUND
void Star::Update(const Vector2& offset) {
	position = initPosition + offset;
}

void Star::Render() {
	DrawCircle((int)position.x, (int)position.y, size, color);
}

Star::Star() {
	initPosition.x = GetRandomValue(-150, GetScreenWidth() + 150);
	initPosition.y = GetRandomValue(0, GetScreenHeight());

	//random color?
	color = SKYBLUE;
	size = GetRandomValue(1, 4) / 2;
}

Background::Background() {
	for (int i = 0; i < STAR_AMOUNT; i++) {
		Star newStar;
		Stars.push_back(newStar);
	}
}

void Background::Update(const Vector2& offset) {
	for(auto &star : Stars) { //updated ranged for loop
		star.Update(offset);
	}
}

void Background::Render() {
	for(auto &s : Stars) {
		s.Render();
	}
}
