#pragma once
#include "raylib.h"
#include "vector"
#include <print>
#include <map>
#include <vector>
#include <format>
#include <algorithm>


using std::string;
using std::vector;
class TextureAtlas { //change to wrapper class, RAII
	public:
	enum struct Textures { SHIP1, SHIP2, SHIP3, ALIEN, BARRIER, LASER };
	typedef std::map<Textures, Texture2D> texture_map;

	TextureAtlas() {
		textures.insert({Textures::ALIEN, LoadTexture("Alien")});
		textures.insert({Textures::LASER, LoadTexture("Laser")});
		textures.insert({Textures::BARRIER, LoadTexture("Barrier")});
		textures.insert({Textures::SHIP1, LoadTexture("Ship1")});
		textures.insert({Textures::SHIP2, LoadTexture("Ship2")});
		textures.insert({Textures::SHIP3, LoadTexture("Ship3")});
	}
	~TextureAtlas() {
		std::for_each(textures.begin(), textures.end(), [](auto& entry) { UnloadTexture(entry.second); });
		textures.clear();
	}

	Texture2D& getTexture(Textures textureName) { return textures[textureName]; }
	Texture2D LoadTexture(const string& assetName) { return ::LoadTexture(std::format("{}{}.png", ASSETS_DIR, assetName).c_str()); }
	texture_map textures;

	TextureAtlas(const TextureAtlas&) = delete;
	TextureAtlas(TextureAtlas&&) = delete;
	TextureAtlas& operator=(const TextureAtlas&) = delete;
	TextureAtlas& operator=(TextureAtlas&&) = delete;
};
