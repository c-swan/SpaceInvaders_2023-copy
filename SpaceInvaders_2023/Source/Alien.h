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

	void Update() {
		position.x += speed * (moveRight ? 1 : -1);

		if (isOutOfBounds()) {
			moveRight = !moveRight;
			position.y += 50;
		}
	}
	const Rectangle& getBounds() const noexcept { return bounds; }
	Circle getCollider() const noexcept { return Circle(position, radius); }
	bool isOutOfBounds() const noexcept { return position.x <= 0 || position.x > GetScreenWidth(); }
	void Render(Renderer& renderer) { renderer.Render(texturePack->getTexture(ALIEN_TEXTURE_NAME), bounds, position); }

	void setPosition(Vector2 pos) noexcept { position = pos; }
	const Vector2& getPosition() const noexcept { return position; }
	bool isDead() const noexcept { return !active; }
	bool isBehindPlayer() const noexcept { return position.y > GetScreenHeight() - PLAYER_BASE_HEIGHT; }
	void hit() noexcept { active = false; }
private:
	TexturePack* texturePack;
};
/*
class AlienSwarm {
public:
	AlienSwarm(int rows, int cols, TexturePack* txtrPck) : texturePack(txtrPck) {
		for (int row = 0; row < ALIEN_FORMATION_HEIGHT; row++) {
			for (int col = 0; col < ALIEN_FORMATION_WIDTH; col++) {
				Aliens.emplace_back(Alien(
								  ALIEN_FORMATION_POS.x + ALIEN_OFFSET_X + (col * ALIEN_SPACING),
								  ALIEN_FORMATION_POS.y + (row * ALIEN_SPACING),
								  texturePack
								  )
							  );
			}
		}
	}
	~AlienSwarm() {
		Aliens.clear();
	}
private:

	std::vector<Alien> Aliens; //rows of aliens

	Vector2 position{0, 0};
	bool moveRight = true;

	TexturePack* texturePack;

public:
	const Vector2& getPosition() const noexcept { return position; }
	Vector2 getAlienPosition(const Alien& alien) { return position + alien.getPosition(); }

	void move() {
		int direction = (moveRight ? 1 : -1);
		position.x += direction * ALIEN_SPEED;
	}
	void flip() {
		moveRight = !moveRight;
		position.y += 50;
	}
	void Render(Renderer& renderer) {
		for(auto& alien : Aliens) {
			renderer.Render(texturePack->getTexture(ALIEN_TEXTURE_NAME), alien.getBounds(), getAlienPosition(alien));
		}
	}
	void Update() {
		move();
		auto outOfBoundAlien = std::find_if(Aliens.begin(), Aliens.end(), [](auto& alien) { return alien.isOutOfBounds(); });
		if(outOfBoundAlien != Aliens.end()) {
			flip();
		}
	}
};
*/
