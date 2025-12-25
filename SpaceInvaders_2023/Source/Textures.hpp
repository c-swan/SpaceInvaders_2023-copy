#pragma once
#include "raylib.h"
#include "vector"
#include <print>

class Textures { //change to wrapper class, RAII
	public:
	Textures() { //TODO: error handling
		alienTexture = LoadTexture("./Assets/Alien.png"); //change ".Assets/" to constant...
		barrierTexture = LoadTexture("./Assets/Barrier.png");
		laserTexture = LoadTexture("./Assets/Laser.png");
		shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
		shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
		shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
		std::println("loaded assets");
	}
	~Textures() {
		UnloadTexture(alienTexture);
		UnloadTexture(barrierTexture);
		for(auto &s : shipTextures) {
			UnloadTexture(s);
		}
		UnloadTexture(laserTexture);
	}
	Texture2D alienTexture;
	Texture2D barrierTexture; //TODO: inconsistent naming
	Texture2D laserTexture;
	std::vector<Texture2D> shipTextures; //does not need to be vector, has const size
};
