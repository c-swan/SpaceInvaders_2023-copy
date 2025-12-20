#pragma once
#include "raylib.h"
#include <vector>
#include "Textures.hpp"
#include "Sounds.hpp"
#include <string>
#include "Constants.h"
#include "Math.hpp"
#include "Window.hpp"
#include "Sounds.hpp"

//TODO: separate classes / structs into files
enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct ProjectileType //TODO: EntityType only used to distinguish projectiles, use derived classes instead
{
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData { //High-Score Data, bad naming
	std::string name;
	int score;
};

struct Player {
public:
	point position{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PLAYER_BASE_HEIGHT};
	float getX() const noexcept { return position.x; }
	float getY() const noexcept { return WINDOW_HEIGHT - PLAYER_BASE_HEIGHT; }
//	float speed = 7; //TODO: constant...

	Rectangle rect {0, 0, PLAYER_SIZE, PLAYER_SIZE};
	float radius = PLAYER_RADIUS; //collider?
	int lives = MAX_LIVES; //TODO: initial value constant
	int direction = 0; //velocity direction x-axis, 0, +1 or -1
	int activeTexture = 0; //texture number...
	float animationTimer = 0; //timer for what?

//	EntityType type = EntityType::PLAYER; //TODO: remove

	void Initialize(); //TODO: move to constructor
	void Update();
	void Render(Texture2D texture); //TODO: pass by const ref

};


struct Projectile {
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	point position = {0,0};
	int speed = -PROJECTILE_SPEED;
	bool active = true;  
	ProjectileType type = ProjectileType::PLAYER_PROJECTILE;

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 }; //what is this line...?
	Vector2 lineEnd = { 0, 0 };

	Rectangle rect = {0, 0, PROJECTILE_SIZE, PROJECTILE_SIZE};
	void Update();
	void Render(Texture2D texture);
};

struct Wall { //TODO: position it correctly
	public:
	point position{0,0};
	Rectangle rect = {0, 0, WALL_SIZE, WALL_SIZE }; //size
	bool active;
//	Color color; 
	int health = WALL_MAX_HEALTH;
	int radius = WALL_RADIUS;

	void Update();
	void Render(Texture2D texture);
};

struct Alien {
	public:
	Alien(int col, int row);
//	Color color = WHITE; //why?
	point position{0,0};
	Rectangle rect {0, 0, ALIEN_SIZE, ALIEN_SIZE};
//	int x = 0;
//	int y = 0;
	float radius = ALIEN_RADIUS;
	bool active = true;
	bool moveRight = true;

//	EntityType type = EntityType::ENEMY;

//	int speed = ALIEN_SPEED;  //const

	void Update();
	void Render(Texture2D texture);
};


struct Star {
	point localPosition = { 0, 0 }; //local position for child,
	point position = { 0, 0 }; //parent position + local position
	Color color = STAR_COLOR; //constant?
	float size = 1;

	void Update();
	void Render();
};

struct Background {
	std::vector<Star> Stars;
	point position = {0,0}; //replaces offset

	void Initialize(); //TODO: use constructor
	void Update();
	void Render();

	void setOffset(float offsetX);
};

class Game {
	public:
	Game();
	~Game();

	void run();

	State gameState = State::STARTSCREEN;

	int score = 0;
	float shootTimer = 0; //Aliens shooting

	bool newHighScore = false;

	void Start(); //StartScreen -> Gameplay
	void End(); // Gameplay -> EndScreen

	void Pause(); //new functionality (Gameplay)

	void Continue(); //EndScreen -> StartScreen
//	void Launch(); //constructor

	void Update();
	void Render();

	void DrawTextCentered(const char *text, int fontSize, Color color);
	void DrawTextCentered(const char *text, Vector2 offset, int fontSize, Color color);
	void DrawTextCenteredHorizontal(const char *text, int posY, int fontSize, Color color);

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);


//high-score / leaderboard
	bool CheckNewHighScore();
	void InsertNewHighScore(std::string name);

	void LoadLeaderboard();
	void SaveLeaderboard();

	// Entity Storage and Resources
	Window window;
	Textures textures;
	Sounds sounds;

	Player player;
	std::vector<Projectile> Projectiles; //TODO: separate into PlayerProjectiles and EnemyProjectiles and get rid of EntityType
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	Background background;

//	Vector2 playerPos; //does not need to be member
//	Vector2 alienPos; //unused
//	Vector2 cornerPos; //does not need to be member
//	float offset; //does not need to be member, keeps getting passed on anyway....
	bool paused = false;

	//TEXTBOX ENTER
	char name[MAX_LETTER_COUNT + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};
