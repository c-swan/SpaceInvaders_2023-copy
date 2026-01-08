#pragma once
#include <raylib.h>
#include <vector>
#include <format>
#include "Constants.h"
#include <string>
#include <unordered_map>

namespace Asset {
	using std::string;
	using std::vector;

	using texture_map = std::unordered_map<string, Texture2D>;
	using audio_map = std::unordered_map<string, Texture2D>;

	enum class TextureName { Alien, Barrier, Laser, Ship1, Ship2, Ship3 };

	inline string getAssetPath(const string assetName) {
		return std::format("{}{}", ASSETS_DIRECTORY, assetName);
	}
	inline Texture2D LoadTextureAsset(const string assetName) {
		return ::LoadTexture( getAssetPath(assetName + ".png").c_str() );
	}

	template <class AssetType>
	class AssetPack {
		public:
		AssetPack() = 0;
		~AssetPack() = 0;
	};

	template <>
	class AssetPack<Texture2D> {
		public:
		AssetPack() {
			string assetNames[] = {"Alien", "Barrier", "Laser", "Ship1", "Ship2", "Ship3"};
			for(auto a : assetNames) {
				textures.push_back(LoadTextureAsset(a))
			}
//			alienTexture = LoadTextureAsset("Alien");
//			barrierTexture = LoadTextureAsset("Barrier");
//			shipTextures.push_back( LoadTextureAsset("Ship1"));
//			shipTextures.push_back( LoadTextureAsset("Ship2"));
//			shipTextures.push_back( LoadTextureAsset("Ship3"));
//			laserTexture = LoadTextureAsset("Laser");
		}
		~AssetPack() {
			UnloadTexture(barrierTexture);
			UnloadTexture(alienTexture);
			for(auto &shipTexture : shipTextures) {
				UnloadTexture(shipTexture);
			}
			UnloadTexture(laserTexture);
		}

		Texture2D& getTexture() const noexcept { return  }

		private:
		u_map <Texture2D> textures;
		vector<Texture2D> shipTextures;
		Texture2D alienTexture;
		Texture2D barrierTexture;
		Texture2D laserTexture;
	};

};
