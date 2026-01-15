#pragma once
#include <raylib.h>
#include "Math.h"
#include "Renderer.h"
#include "TexturePack.hpp"

class Player {
public:
	Player(TexturePack* txtPck) : texturePack(txtPck) {
		position.y = Window::Height - PLAYER_BASE_HEIGHT;
		position.x = Window::Width / 2;
	}
	~Player() = default;

	int animation_frame = 0;
	float animation_timer = 0;
	
	float getX() const noexcept { return position.x; }
	const Vector2& getPosition() const noexcept { return position; }
	Circle getCollider() const noexcept { return Circle(position, radius);}

	void Render(Renderer& renderer) { renderer.Render(getTexture(), getRect(PLAYER_SIZE), position); }
	void Update() {
		move();
		animate();
	}
	void move() {
		if (IsKeyDown(KEY_LEFT)) { position.x -= PLAYER_SPEED; }
		if (IsKeyDown(KEY_RIGHT)) { position.x += PLAYER_SPEED; }
		position.x = std::clamp(position.x, radius, (Window::Width - radius));
	}
	void animate() {
		animation_timer += GetFrameTime();
		if (animation_timer > PLAYER_ANIMATION_FRAME_DURATION) {
			(++animation_frame) %= SHIP_TEXTURE_COUNT;
			animation_timer = 0;
		}
	}

	Texture2D* getTexture() { return texturePack->getShipTexture(animation_frame); }
	bool isDead() const noexcept { return lives < 1; }
	int getLives() const noexcept { return lives; }
	void hit() noexcept { lives = std::clamp(--lives, 0, PLAYER_MAX_LIVES); }
private:
	Vector2 position;
	TexturePack* texturePack;
	float radius = PLAYER_RADIUS;
	int lives = PLAYER_MAX_LIVES;

};
