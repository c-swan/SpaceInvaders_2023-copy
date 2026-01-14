#include "Gameplay.hpp"
#include "EndScreen.hpp"
#include "game.h"

Gameplay::Gameplay(Game* game) : GameScene(game), player(&game->texturePack), alienSwarm(ALIEN_FORMATION_ROWS, ALIEN_FORMATION_COLUMNS, &game->texturePack) {
	if(_game == nullptr) {
		throw ErrorType::NULLPTR_GAME;
	}

	Stars.resize(STAR_COUNT);
	scoreText = TextUI(std::format("Score: {}", score), {50, 20});
	livesText = TextUI(std::format("Lives: {}", player.lives), {50, 70});
	SpawnBunkers();
}

void Gameplay::SpawnBunkers() {
	for (int i = 0; i < BUNKER_COUNT; i++) {
		Bunkers.emplace_back( Bunker(
						     Window::Width * (i + 1) / (BUNKER_COUNT + 1),
						     Window::Height - BUNKER_POSITION_Y,
						     &_game->texturePack)
					   );
	}
}


std::optional<GameScene*> Gameplay::Update() {
	if (IsKeyReleased(KEY_Q)) {
		return GameOver();
	}

	player.Update();
	alienSwarm.Update();

	if(alienSwarm.isBehindPlayer()) {
		return GameOver();
	}

	UpdateStarPositions();

	for(auto& projectile : Projectiles) {
		projectile.move();
	}

	if (IsKeyPressed(KEY_SPACE)) {
		MakePlayerProjectile();
	}

	AliensShooting();
	CheckAllCollisions();
	RemoveInactiveEntities();

	if(player.isDead()) {
		return GameOver();
	}

	return Continue();
}

void Gameplay::MakePlayerProjectile() {
	Projectiles.emplace_back(
					 Projectile(
							Projectile::Type::Player,
							{ player.getX(), Window::Height - PROJECTILE_BASE_POS_Y },
							&_game->texturePack
							)
					 );
}

void Gameplay::Render(Renderer& renderer) {
	for(auto& star : Stars) {
		star.Render(renderer);
	}
	renderer.DrawText(scoreText);
	renderer.DrawText(livesText);
	player.Render(renderer);
	alienSwarm.Render(renderer);
	for(auto& bunker : Bunkers) {
		bunker.Render(renderer);
	}
	for(auto& projectile : Projectiles) {
		projectile.Render(renderer);
	}
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
void Gameplay::setScore(int s) {
	score = s;
	scoreText.text = std::format("Score: {}", score);
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
		livesText.text = std::format("Lives: {}", player.lives);
	}
}
void Gameplay::CheckCollision(Bunker& bunker, Projectile& projectile) {
	if (CheckCollision(bunker.getCollider(), projectile.getCollider())) {
		projectile.hit();
		bunker.hit();
	}
}

void Gameplay::RemoveInactiveEntities() {
	std::erase_if(Projectiles, [](auto& projectile) { return !projectile.isActive() || projectile.isOutOfBounds(); });
	std::erase_if(Bunkers, [](auto& bunker) { return bunker.isDead(); });
	alienSwarm.RemoveInactiveAliens();
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
						   &_game->texturePack
						   )
				    );
	alienShootTimer = 0;
}

EndScreen* Gameplay::GameOver() noexcept { return new EndScreen(_game, score); }
