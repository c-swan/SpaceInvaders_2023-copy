#pragma once
#include "Renderer.h"
#include "Assets.h"
#include <algorithm>

struct Alien {
	Vector2 position;
	float radius = ALIEN_RADIUS;
	bool active = true;
	bool moveRight = true;
	Rectangle bounds {0, 0, 100, 100};

	int speed = ALIEN_SPEED;
	Alien(float x, float y, TexturePack* txtrPck) : texturePack(txtrPck), position(Vector2(x, y)) { }

	const Rectangle& getBounds() const noexcept { return bounds; }
	Circle getCollider() const noexcept { return Circle(getPosition(), radius); }
	bool isOutOfBounds() const noexcept { return getPosition().x <= 0 || getPosition().x > GetScreenWidth(); }
	void Render(Renderer& renderer) { renderer.Render(texturePack->getTexture(ALIEN_TEXTURE_NAME), bounds, getPosition()); }

	void setPosition(Vector2 pos) noexcept { position = pos; }
	Vector2 getLocalPosition() const noexcept { return position; }
	Vector2 getPosition() const noexcept { return swarmPosition + position; }
	bool isDead() const noexcept { return !active; }
	bool isBehindPlayer() const noexcept { return getPosition().y > GetScreenHeight() - PLAYER_BASE_HEIGHT; }
	void hit() noexcept { active = false; }

	static Vector2 swarmPosition;
private:
	TexturePack* texturePack;
};

class AlienSwarm {
public:
	AlienSwarm(int r, int c, TexturePack* txtrPck) : texturePack(txtrPck), rows(r), cols(c) {
		SpawnAliens(rows, cols);
	}
	~AlienSwarm() {
		Aliens.clear();
	}
	void SpawnAliens(int rows, int cols) {
		Alien::swarmPosition = {0, 0};
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				Aliens.emplace_back(Alien(
								  ALIEN_FORMATION_POS.x + ALIEN_OFFSET_X + (col * ALIEN_SPACING),
								  ALIEN_FORMATION_POS.y + (row * ALIEN_SPACING),
								  texturePack
								  )
							  );
			}
		}
	}
	std::vector<Alien>& getAliens() noexcept { return Aliens; }
	int rows, cols;
private:

	std::vector<Alien> Aliens; //rows of aliens

//	Vector2 position{0, 0};
	bool moveRight = true;

	TexturePack* texturePack;

public:
	const Vector2& getPosition() const noexcept { return Alien::swarmPosition; }
//	Vector2 getAlienPosition(const Alien& alien) { return Alien::swarmPosition + alien.getPosition(); }

	bool isBehindPlayer() {
		auto alien_behind_player = std::ranges::find_if(Aliens, [](auto& alien) { return alien.isBehindPlayer(); } );
		return (alien_behind_player != Aliens.end());
	}
	void move() {
		int direction = (moveRight ? 1 : -1);
		Alien::swarmPosition.x += direction * ALIEN_SPEED;
	}
	void flip() {
		moveRight = !moveRight;
		Alien::swarmPosition.y += 50;
	}
	void Render(Renderer& renderer) {
		for(auto& alien : Aliens) {
			alien.Render(renderer);
		}
	}
	void Update() {
		move();
		auto outOfBoundAlien = std::find_if(Aliens.begin(), Aliens.end(), [](auto& alien) { return alien.isOutOfBounds(); });
		if(outOfBoundAlien != Aliens.end()) {
			flip();
		}
		if(empty()) SpawnAliens(rows, cols);
	}
	void RemoveInactiveAliens() { std::erase_if(Aliens, [](auto& alien) { return alien.isDead(); }); }

	bool empty() const noexcept { return Aliens.empty(); }
	int size() const noexcept { return static_cast<int>(Aliens.size()); }
	Vector2 getRandomAlienPosition() {
		int randomAlienIndex = GetRandomValue(0, size() - 1);
		return Aliens[randomAlienIndex % Aliens.size()].getPosition();
	}

};

