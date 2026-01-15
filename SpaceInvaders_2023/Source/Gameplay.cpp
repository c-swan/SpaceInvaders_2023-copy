#include "Gameplay.hpp"
#include "EndScreen.hpp"
#include "game.h"

float Star::offset_x = 0;
Vector2 Alien::swarm_position = {0,0};

Gameplay::Gameplay(Game* game) : GameScene(game), player(&game->texture_pack), alienSwarm(&game->texture_pack) {
	if(_game == nullptr) {
		throw ErrorType::NULLPTR_GAME;
	}
	Stars.resize(STAR_COUNT);
	SpawnBunkers();
}

std::optional<GameScene*> Gameplay::Update() {
	if (IsKeyReleased(KEY_Q)) {
		return GameOver();
	}

	player.Update();
	alienSwarm.Update();

	Star::offset_x = player.getX() / -PARALLAX_FACTOR;

	std::ranges::for_each(Projectiles, [](auto& projectile) { projectile.move(); } );

	if (IsKeyPressed(KEY_SPACE)) {
		MakePlayerProjectile();
	}

	AliensShooting();
	CheckAllCollisions();
	RemoveInactiveEntities();

	if(player.isDead() || alienSwarm.isBehindPlayer()) {
		return GameOver();
	}
	return Continue();
}

void Gameplay::Render(Renderer& renderer) {
	for(auto& star : Stars) {
		star.Render(renderer);
	}
	player.Render(renderer);
	alienSwarm.Render(renderer);
	for(auto& bunker : Bunkers) {
		bunker.Render(renderer);
	}
	for(auto& projectile : Projectiles) {
		projectile.Render(renderer);
	}
	renderer.DrawText(scoreText);
	renderer.DrawText(livesText);
}

void Gameplay::CheckAllCollisions() {
	for(auto &projectile : Projectiles) {
		if (projectile.isActive()) {
			if(projectile.isPlayerProjectile()) {
				for(auto &alien : alienSwarm.getAliens()) {
					CheckCollision(alien, projectile);
				}
			}
			else if(projectile.isAlienProjectile() && projectile.isWithinPlayerRange()) {
				CheckCollision(player, projectile);
			}
			if(projectile.isWithinBunkerRange()) {
				for(auto &bunker : Bunkers) {
					CheckCollision(bunker, projectile);
				}
			}
		}
	}
}
void Gameplay::CheckCollision(Alien& alien, Projectile& projectile) {
	if (CheckCollision(alien.getCollider(), projectile.getCollider())) {
		projectile.hit();
		alien.hit();
		setScore(score + ALIEN_HIT_SCORE);
	}
}
void Gameplay::CheckCollision(Player& player, Projectile& projectile) {
	if (CheckCollision(player.getCollider(), projectile.getCollider())) {
		projectile.hit();
		player.hit();
		livesText.text = std::format("Lives: {}", player.getLives());
	}
}
void Gameplay::CheckCollision(Bunker& bunker, Projectile& projectile) {
	if (CheckCollision(bunker.getCollider(), projectile.getCollider())) {
		projectile.hit();
		bunker.hit();
	}
}
bool Gameplay::DrawColliders(const Circle &circle, const Rectangle &rect, bool collision) {
	DrawRectangleLinesEx(rect, 5, collision ? GREEN : RED);
	DrawCircleV(circle.center, circle.radius, collision ? GREEN : RED);
	return collision;
}

void Gameplay::RemoveInactiveEntities() {
	std::erase_if(Projectiles, [](auto& projectile) { return !projectile.isActive() || projectile.isOutOfBounds(); });
	std::erase_if(Bunkers, [](auto& bunker) { return bunker.isDead(); });
	alienSwarm.RemoveInactiveAliens();
}

void Gameplay::SpawnBunkers() {
	for (int i = 0; i < BUNKER_COUNT; i++) {
		Bunkers.emplace_back( Bunker(
						     Window::Width * (i + 1) / (BUNKER_COUNT + 1),
						     Window::Height - BUNKER_POSITION_Y,
						     &_game->texture_pack ) );
	}
}

void Gameplay::MakePlayerProjectile() {
	Projectiles.emplace_back( Projectile(
							 Projectile::Type::Player,
							 { player.getX(), Window::Height - PROJECTILE_BASE_POS_Y },
							 &_game->texture_pack ) );
}
void Gameplay::AliensShooting() {
	if (alienSwarm.empty()) {
		return;
	}
	alienShootTimer++;
	if (alienShootTimer < ALIEN_SHOOT_TIME) {
		return;
	}

	Projectiles.push_back(Projectile(
						   Projectile::Type::Alien,
						   alienSwarm.getRandomAlienPosition(),
						   &_game->texture_pack ) );
	alienShootTimer = 0;
}

void Gameplay::setScore(int s) noexcept {
	scoreText.text = std::format("Score: {}", score = s);
}

EndScreen* Gameplay::GameOver() noexcept {
	return new EndScreen(_game, score);
}
