//
//  Entities.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef Entities_hpp
#define Entities_hpp
#include <vector>
#include <string>
#include <raylib.h>
#include "Math.hpp"

enum struct EntityType //how about classes!
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData { //could be string int map?
	std::string name;
	int score;
};

class Player {
public:
	Player();
	Vector2 position;

	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	EntityType type = EntityType::PLAYER; //we have classes

	void Initialize(); //we have constructors
	void Render(Texture2D texture);
	void Update();

};


struct Projectile {
	public:
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY
	explicit Projectile(Vector2& pos, EntityType et);
	Vector2 position{0,0};
	bool active = true;
	EntityType type{};

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS ???
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();
	void Render(Texture2D texture);
};

struct Wall {
	Vector2 position;
	Rectangle rec; //includes pos but whatever...

	bool active;
	Color color;

	int health = 50;
	int radius = 60;

	void Render(Texture2D texture);
	void Update();
};

struct Alien {
	Color color = WHITE;
	Vector2 position = {0, 0};
	int x = 0; //TODO: redundant?
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	EntityType type = EntityType::ENEMY;

	void Update();
	void Render(Texture2D texture);
};


struct Star {
	explicit Star();
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	
	void Update(const Vector2 &starOffset);
	void Render();
};

struct Background {
	explicit Background();
	std::vector<Star> Stars;

//	void Initialize();
	void Update(const Vector2 &offset);
	void Render();
};

#endif /* Entities_hpp */
