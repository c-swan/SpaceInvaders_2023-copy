#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Renderer.h"
#include "Assets.h"
#include "Math.h"
struct Bunker {
	Bunker(float x, float y, TexturePack* txtrPck) : texturePack(txtrPck) { position.x = x; position.y = y; }
	void Render(Renderer& renderer) {
		renderer.Render(texturePack->getTexture("Barrier"), bounds, position);
		renderer.DrawText(std::to_string(health), position + textPosition, DEFAULT_FONT_SIZE, BUNKER_TEXT_COLOR);
	}
	Vector2 getPosition() { return position; }
	void setHealth(int h) noexcept {
		health = std::clamp(h, 0, maxHealth);
		if(active && isDead()) active = false;
	}
	TexturePack* texturePack;

	bool isDead() const noexcept { return health < 1; }
	void hit() noexcept { setHealth(health - 1); }
	Circle getCollider() { return Circle(position, radius); }
	float getRadius() { return radius; }
	bool active = true;
private:
	Vector2 position;
	Rectangle bounds{0, 0, 200, 200}; //size

	int radius = BUNKER_RADIUS;
	int maxHealth = BUNKER_MAX_HEALTH;
	int health = maxHealth;

	Vector2 textPosition {-21, 10};
};
