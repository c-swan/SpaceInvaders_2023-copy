#pragma once
#include <raylib.h>
#include "Renderer.h"
#include "Constants.h"
#include "Assets.h"

struct Projectile {
	enum Type { Player, Alien } type = Type::Player;
	Projectile(Type t, Vector2 pos, TexturePack* txtrPck) : type(t), position(pos), texturePack(txtrPck) {
		if(isPlayerProjectile()) {
			direction = -1;
		}
		if(isAlienProjectile()) {
			position.y += 40;
		}
	}

	Vector2 position;
	int direction = 1;
	bool active = true;

	Rectangle bounds {0, 0, 50, 50};
	TexturePack *texturePack;
	void Update() {
		position.y += direction * PROJECTILE_SPEED;

		if (isOutOfBounds()) {
			active = false;
		}
	}

	void Render(Renderer& renderer) { renderer.Render(texturePack->getTexture(PROJECTILE_TEXTURE_NAME), bounds, position); }

	bool isActive() const noexcept { return active; }
	bool isOutOfBounds() const noexcept { return position.y < 0 || position.y > 1500; }
	bool isWithinBunkerRange() noexcept { return (position.y > GetScreenHeight() - BUNKER_POSITION_Y - BUNKER_RADIUS - getWidth() / 2) && (position.y < GetScreenHeight() - BUNKER_POSITION_Y + BUNKER_RADIUS + getWidth() / 2); }
	bool isWithinPlayerRange() noexcept { return (position.y > GetScreenHeight() - PLAYER_BASE_HEIGHT - PLAYER_RADIUS - PROJECTILE_HEIGHT / 2); }

	Vector2 getPosition() const noexcept { return position; }
	Rectangle getCollider() const noexcept { return Rectangle(position.x - (getWidth() / 2), position.y - (getHeight() / 2), getWidth(), getHeight());}
	float getWidth() const noexcept { return PROJECTILE_WIDTH; }
	float getHeight() const noexcept { return PROJECTILE_HEIGHT; }
	bool isPlayerProjectile() const noexcept  { return type == Player; }
	bool isAlienProjectile() const noexcept { return type == Alien; }
	void hit() noexcept { active = false; }
};
