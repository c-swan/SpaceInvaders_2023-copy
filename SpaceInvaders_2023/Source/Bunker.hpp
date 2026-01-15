#pragma once
#include <raylib.h>
#include "Constants.hpp"
#include "Renderer.hpp"
#include "TexturePack.hpp"
#include "Math.hpp"
#include "TextUI.hpp"

struct Bunker {
	Bunker(float x, float y, TexturePack* txtrPck) : texture_pack(txtrPck), position{x, y} {

		healthText.position = getPosition();
		healthText.text = std::to_string(health);
		healthText.offset.y = 10;
		healthText.CenterAlign();
		healthText.fontColor = BUNKER_TEXT_COLOR;
	}
	void Render(Renderer& renderer) {
		if(isDead()) {
			return;
		}
		renderer.Render(texture_pack->getTexture(BUNKER_TEXTURE_NAME), getRect(BUNKER_SIZE), position);
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
	TexturePack* texture_pack;
	Vector2 position;

	int radius = BUNKER_RADIUS;
	int maxHealth = BUNKER_MAX_HEALTH;
	int health = maxHealth;
//	Vector2 textPosition{0, 10}; //-21
	TextUI healthText;
};
