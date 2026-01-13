#pragma once
#include "Entities.hpp"
#include "Renderer.h"
#include "Assets.h"

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
	Circle getCollider() const noexcept { return Circle(position, radius); }
	bool isOutOfBounds() { return position.x <= 0 || position.x > GetScreenWidth(); }
	void Render(Renderer& renderer) { renderer.Render(texturePack->getTexture("Alien"), bounds, position); }

	void setPosition(Vector2 pos) noexcept { position = pos; }
	Vector2 getPosition() { return position; }
	bool isDead() const noexcept { return !active; }
	bool isBehindPlayer() { return position.y > GetScreenHeight() - PLAYER_BASE_HEIGHT; }
	void hit() noexcept { active = false; }
private:
	TexturePack* texturePack;
};
