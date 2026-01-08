#pragma once
#include <raylib.h>
#include <vector>
#include <format>
#include "Constants.h"
#include <string>
#include <unordered_map>
#include <exception>


	using std::string;
	using std::vector;

	inline string getAssetPath(const string assetName) {
		return std::format("{}{}", ASSETS_DIRECTORY, assetName);
	}
	template <typename T>
	inline T LoadAsset(const string assetName) {
		throw std::exception(std::format("Loading unspecified asset: {}", typeid(T).name()) );
		return T();
	}
	template <>
	inline Sound LoadAsset<Sound>(const string assetName) {
		return ::LoadSound( getAssetPath(assetName + ".ogg").c_str() );
	}
	template <>
	inline Texture2D LoadAsset<Texture2D>(const string assetName) {
		return ::LoadTexture( getAssetPath(assetName + ".png").c_str() );
	}

	inline void UnloadAsset(Texture2D& texture) { UnloadTexture(texture); }
	inline void UnloadAsset(Sound& sound) { UnloadSound(sound); }


template <typename T>
struct Asset {
	static_assert(std::is_base_of<Texture2D, T>() || std::is_base_of<Sound, T>() || std::is_base_of<Font, T>());
	Asset(string name) { _asset = std::make_unique<T>(LoadAsset<T>(name)); }
	~Asset() { UnloadAsset(getAsset());}

	T& getAsset() const noexcept { return *_asset; }
	protected:
	std::unique_ptr<T> _asset;
};

using texture_map = std::unordered_map<string, Texture2D>;
using sound_map = std::unordered_map<string, Sound>;


	template <class AssetType>
	class AssetPack {
		public:
		AssetPack() = 0;
		~AssetPack() = 0;

		AssetPack(const AssetPack&) = delete;
		AssetPack(AssetPack&&) = delete;
		AssetPack& operator=(const AssetPack&) = delete;
		AssetPack& operator=(AssetPack&&) = delete;
	};

	template <>
	class AssetPack<Texture2D> {
		public:
		AssetPack() {
			for(auto a : names) {
				textures.insert({a, LoadAsset<Texture2D>(a)});
			}
		}
		~AssetPack() {
			for(auto& t : textures) {
				UnloadAsset(t.second);
			}
		}

		private:
		vector<string> names = {"Alien", "Barrier", "Laser", "Ship1", "Ship2", "Ship3"};
		texture_map textures;

		public:
		Texture2D& getTexture(string textureName) {
			if(!textures.contains(textureName)) {
				throw std::runtime_error(std::format("Texture {} not found.", textureName));
			}
			return textures[textureName];
		}
		Texture2D& getShipTexture(int n) { return getTexture(std::format("Ship{}", (n % 3) + 1)); }
	};
	using TexturePack = AssetPack<Texture2D>;

	template <>
	class AssetPack<Sound> {
		public:
		AssetPack() {
			InitAudioDevice();
			if(!IsAudioDeviceReady()) {
				throw std::runtime_error("Audio device not loaded");
			}
			for(auto s : soundNames) {
				sounds.insert({s, LoadAsset<Sound>(s)});
			}
		}
		~AssetPack() {
			for(auto& s : sounds) {
				UnloadAsset(s.second);
			}
			CloseAudioDevice();
		}

		private:
		string soundNames[1] = { "hitHurt"}; //should load from file
		sound_map sounds;

		public:
		Sound& getSound(string soundName) {
			if(!sounds.contains(soundName)) {
				throw std::runtime_error(std::format("Sound {} not found.", soundName));
			}
			return sounds[soundName];
		}
	};
	using SoundPack = AssetPack<Sound>;

