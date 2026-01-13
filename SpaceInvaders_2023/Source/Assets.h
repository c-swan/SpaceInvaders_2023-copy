#pragma once
#include <raylib.h>
#include <map>
#include <vector>
#include <string>
#include <format>
#include <exception>
#include <algorithm>
#include "Constants.h"
#include "Math.h"

inline std::string getAssetPath(const std::string assetName) { return std::format("{}{}", ASSETS_DIRECTORY, assetName); }
inline Texture2D LoadTextureAsset(const std::string assetName) { return ::LoadTexture( getAssetPath(assetName + ".png").c_str() ); }

class TexturePack {
	public:
	TexturePack() {
		for(auto name : names) {
			textures.insert( { name, LoadTextureAsset(name) } );
		}
	}
	~TexturePack() {
		for(auto texture : textures) {
			UnloadTexture(texture.second);
		}
		textures.clear();
	}

	private:
	std::vector<std::string> names = {"Alien", "Barrier", "Laser", "Ship1", "Ship2", "Ship3"};
	std::map<std::string, Texture2D> textures{};

	public:
	Texture2D* getTexture(std::string textureName) {
		if(!textures.contains(textureName)) {
			throw std::runtime_error(std::format("Texture {} not found.", textureName));
		}
		return &textures[textureName];//.getTexture();
	}
	Texture2D* getShipTexture(int n) { return getTexture(std::format("Ship{}", (n % SHIP_TEXTURE_COUNT) + 1)); }
};
