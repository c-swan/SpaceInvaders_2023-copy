#pragma once
#include <raylib.h>
#include "Renderer.hpp"
#include "Constants.hpp"
#include "TexturePack.hpp"
#include "ErrorHandling.hpp"

struct Projectile {
	enum Type { Player, Alien } type = Type::Player;
	Projectile(Type t, Vector2 pos, TexturePack* txtrPck) : type(t), position(pos), texturePack(txtrPck) {
		if(texturePack == nullptr) {
			throw ErrorType::NULLPTR_TEXTURE_PACK; //std::runtime_error("projectile TexturePack == nullptr");
		}
		if(isAlienProjectile()) {
			direction = 1;
			position.y += 40;
		}
	}

	Vector2 position;
	TexturePack *texturePack;

	void move() { position.y += direction * PROJECTILE_SPEED; }
	void Render(Renderer& renderer) { renderer.Render(texturePack->getTexture(PROJECTILE_TEXTURE_NAME), bounds, position); }

	bool isActive() const noexcept { return active; }
	bool isOutOfBounds() const noexcept { return position.y < -PROJECTILE_HEIGHT / 2 || position.y > Window::Height + PROJECTILE_HEIGHT / 2; }
	bool isWithinBunkerRange() const noexcept { return (position.y > Window::Height - BUNKER_POSITION_Y - BUNKER_RADIUS - PROJECTILE_HEIGHT / 2) && (position.y < Window::Height - BUNKER_POSITION_Y + BUNKER_RADIUS + PROJECTILE_HEIGHT / 2); }
	bool isWithinPlayerRange() const noexcept { return (position.y > Window::Height - PLAYER_BASE_HEIGHT - PLAYER_RADIUS - PROJECTILE_HEIGHT / 2); }

	const Vector2& getPosition() const noexcept { return position; }
	Rectangle getCollider() const noexcept { return Rectangle(position.x - PROJECTILE_WIDTH / 2, position.y - PROJECTILE_HEIGHT / 2, PROJECTILE_WIDTH, PROJECTILE_HEIGHT); }
	float getWidth() const noexcept { return PROJECTILE_WIDTH; }
	float getHeight() const noexcept { return PROJECTILE_HEIGHT; }

	const Rectangle& getBounds() const noexcept { return bounds; }

	bool isPlayerProjectile() const noexcept  { return type == Player; }
	bool isAlienProjectile() const noexcept { return type == Alien; }

	void hit() noexcept { active = false; }
private:
	int direction = -1;
	bool active = true;
	Rectangle bounds {0, 0, 50, 50};

};
