#pragma once
#include <raylib.h>
#include <map>
#include <vector>
#include <string>
#include <format>
#include <algorithm>

#include "ErrorHandling.hpp"
#include "Constants.hpp"
#include "Math.hpp"

inline Texture2D LoadTextureAsset(const std::string& assetName) { return ::LoadTexture(std::format("{}{}.png", ASSETS_DIRECTORY, assetName).c_str() ); }

class TexturePack {
	public:
	TexturePack() {
		for(auto name : texture_names) {
			LoadTextureAsset(name);
			if(!IsTextureValid(textures[name])) {
				throw ErrorMessage{ErrorType::TEXTURE_INVALID, name};
			}
		}
	}
	~TexturePack() {
		for(auto texture : textures) {
			UnloadTexture(texture.second);
		}
	}

	Texture2D* getTexture(std::string textureName) {
		if(!textures.contains(textureName)) {
			throw std::runtime_error(std::format("Texture {} not found.", textureName));
		}
		return &textures[textureName];
	}

	Texture2D* getProjectileTexture() noexcept { return getTexture("Laser"); }
	Texture2D* getBunkerTexture() noexcept { return getTexture("Barrier"); }
	Texture2D* getAlienTexture() noexcept { return getTexture("Alien"); }
	Texture2D* getShipTexture(int n) { return getTexture(std::format("Ship{}", (n % SHIP_TEXTURE_COUNT) + 1)); }

	TexturePack(const TexturePack&) = delete;
	TexturePack(TexturePack&&) = delete;
	TexturePack& operator=(const TexturePack&) = delete;
	TexturePack& operator=(TexturePack&&) = delete;

	private:
	std::vector<std::string> texture_names = {"Alien", "Barrier", "Laser", "Ship1", "Ship2", "Ship3"};
	std::map<std::string, Texture2D> textures{};

	void LoadTextureAsset(const std::string& name) { textures.insert({name, LoadTexture(std::format("{}{}.png", ASSETS_DIRECTORY, name).c_str() )}); }

};
