#pragma once
#include <raylib.h>
#include <vector>
#include <format>
#include "Constants.h"
#include <string>

inline Texture2D LoadTextureNamed(const std::string assetName) {
	return LoadTexture( std::format("{}{}.png", ASSETS_DIR, assetName).c_str() );
}
class Resources {
public:
	Resources() {
		alienTexture = LoadTextureNamed("Alien");
		barrierTexture = LoadTextureNamed("Barrier");
		shipTextures.push_back( LoadTextureNamed("Ship1"));
		shipTextures.push_back( LoadTextureNamed("Ship2"));
		shipTextures.push_back( LoadTextureNamed("Ship3"));
		laserTexture = LoadTextureNamed("Laser");
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

