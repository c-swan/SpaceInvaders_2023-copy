#pragma once
#include "Renderer.h"
#include "Assets.h"
#include <algorithm>

struct Alien {
	Alien(float x, float y) : position{x, y} { }

	const Rectangle& getBounds() const noexcept { return bounds; }
	Circle getCollider() const noexcept { return Circle(getPosition(), radius); }
	bool isOutOfBounds() const noexcept { return getPosition().x < 0 || getPosition().x > Window::Width; }
//	void Render(Renderer& renderer) { if(active) { renderer.Render(texturePack->getTexture(ALIEN_TEXTURE_NAME), bounds, getPosition()); } }

	void setPosition(Vector2 pos) noexcept { position = pos; }
	Vector2 getPosition() const noexcept { return swarm_position + position; }
	bool isDead() const noexcept { return !active; }
	bool isBehindPlayer() const noexcept { return getPosition().y > Window::Height - PLAYER_BASE_HEIGHT; }
	void hit() noexcept { active = false; }

	static Vector2 swarm_position;
private:
	Vector2 position;
	Rectangle bounds {0, 0, 100, 100};
	bool active = true;
	float radius = ALIEN_RADIUS;

};

class AlienSwarm {
public:
	AlienSwarm(int r, int c, TexturePack* txtrPck) : texturePack(txtrPck), rows(r), cols(c) {
		SpawnAliens();
	}
	~AlienSwarm() {
		Aliens.clear();
	}
	void SpawnAliens() {
		Alien::swarm_position = {0, 0};
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				Aliens.emplace_back(Alien(
								  ALIEN_FORMATION_POS.x + ALIEN_OFFSET_X + (col * ALIEN_SPACING),
								  ALIEN_FORMATION_POS.y + (row * ALIEN_SPACING)
								  )
							  );
			}
		}
	}
	std::vector<Alien>& getAliens() noexcept { return Aliens; }
private:
	std::vector<Alien> Aliens;
	int rows, cols;
	bool move_right = true;
	TexturePack* texturePack;

public:
	bool isBehindPlayer() {
		auto alien_behind_player = std::ranges::find_if(Aliens, [](auto& alien) { return alien.isBehindPlayer(); } );
		return (alien_behind_player != Aliens.end());
	}
	void move() { Alien::swarm_position.x += (move_right ? 1 : -1) * ALIEN_SPEED; }
	void flip() {
		move_right = !move_right;
		Alien::swarm_position.y += ALIEN_MOVE_DOWN_DISTANCE;
	}
	void Render(Renderer& renderer) {
		for(auto& alien : Aliens) {
			renderer.Render(texturePack->getTexture(ALIEN_TEXTURE_NAME), alien.getBounds(), alien.getPosition());
		}
	}
	void Update() {
		if(empty()) {
			SpawnAliens();
		}
		move();
		if(isAnyAlienOutOfBounds()) {
			flip();
		}
	}

	bool isAnyAlienOutOfBounds() {
		auto out_of_bounds_alien = std::ranges::find_if(Aliens, [](auto& alien) { return alien.isOutOfBounds(); });
		return out_of_bounds_alien != Aliens.end();
		return out_of_bounds_alien != Aliens.end();
	}
	void RemoveInactiveAliens() { std::erase_if(Aliens, [](auto& alien) { return alien.isDead(); }); }
	Vector2 getRandomAlienPosition() const noexcept { return Aliens[GetRandomValue(0, size() - 1) % Aliens.size()].getPosition(); }

	bool empty() const noexcept { return Aliens.empty(); }
	int size() const noexcept { return static_cast<int>(Aliens.size()); }


};

