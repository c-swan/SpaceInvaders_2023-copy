#pragma once
#include <raylib.h>
#include "Constants.h"
#include "Renderer.h"
#include "Assets.h"
#include "Math.h"
#include "TextUI.h"

struct Bunker {
	Bunker(float x, float y, TexturePack* txtrPck) : texturePack(txtrPck), position{x, y} {

		healthText.position = textPosition + getPosition();
		healthText.text = std::to_string(health);
		healthText.fontColor = BUNKER_TEXT_COLOR;
	}
	void Render(Renderer& renderer) {
		if(isDead()) {
			return;
		}
		renderer.Render(texturePack->getTexture(BUNKER_TEXTURE_NAME), bounds, position);
		renderer.DrawText(healthText);
	}
	void setHealth(int h) noexcept {
		health = std::clamp(h, 0, maxHealth);
		healthText.text = std::to_string(health);
	}

	const Vector2& getPosition() const noexcept { return position; }
	Circle getCollider()  const noexcept { return Circle(position, radius); }
	float getRadius()  const noexcept { return radius; }

	bool isDead() const noexcept { return health < 1; }
	void hit() noexcept { setHealth(health - 1); }

private:
	TexturePack* texturePack;
	Vector2 position;
	Rectangle bounds{0, 0, BUNKER_SIZE, BUNKER_SIZE}; //size

	int radius = BUNKER_RADIUS;
	int maxHealth = BUNKER_MAX_HEALTH;
	int health = maxHealth;
	Vector2 textPosition{-21, 10};
	TextUI healthText;
};
