#pragma once
#include "raylib.h"
#include <vector>
#include <format>
#include "Constants.h"

inline Texture2D LoadTexture(std::string assetName) {
	return LoadTexture(std::format("{}{}.png", ASSETS_DIR, assetName).c_str());
}

struct Resources {
	Resources() {
		alienTexture = LoadTexture("Alien");
		barrierTexture = LoadTexture("Barrier");
		for(int i=1; i<=SHIP_TEXTURE_COUNT; i++) {
			shipTextures.push_back(LoadTexture(std::format("Ship{}", i)));
		}
		laserTexture = LoadTexture("Laser");
	}
	~Resources() {
		UnloadTexture(barrierTexture);
		UnloadTexture(alienTexture);
		for(auto &shipTexture : shipTextures) {
			UnloadTexture(shipTexture);
		}
		UnloadTexture(laserTexture);
	}

	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;
};
