#pragma once
#include "raylib.h"
#include "vector"
#include <print>
#include <map>
#include <format>
#include <algorithm>

enum struct TextureName { SHIP1, SHIP2, SHIP3, ALIEN, BARRIER, LASER };

typedef std::map<TextureName, Texture2D> texture_map;
using std::string;

class TextureAtlas { //change to wrapper class, RAII
	public:
	Textures() {

		Texture2D alienTexture = LoadTexture("Alien");
		textures.insert({TextureName::ALIEN, alienTexture});
		textures.insert({LASER_TEXTURE, LoadTexture("Laser")});
		textures.insert({BARRIER_TEXTURE, LoadTexture("Barrier")});
		textures.insert({SHIP1_TEXTURE, LoadTexture("Ship1")});
		textures.insert({SHIP2_TEXTURE, LoadTexture("Ship2")});
		textures.insert({SHIP3_TEXTURE, LoadTexture("Ship3")});
	}
	~Textures() {
		std::for_each(textures.begin(), textures.end(), [](std::pair<TextureName, Texture2D> entry) { UnloadTexture(entry.second);});
		textures.clear();
	}

	Texture2D& getTexture(TextureName textureName) { return textures[textureName]; }
	Texture2D LoadTexture(const string& assetName) { return ::LoadTexture(std::format("{}{}.png", ASSETS_DIR, assetName).c_str()); }
	texture_map textures;
};
