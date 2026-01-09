#pragma once
#include <raylib.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <format>
#include <exception>
#include <algorithm>
#include "Constants.h"

inline std::string getAssetPath(const std::string assetName) {
	return std::format("{}{}", ASSETS_DIRECTORY, assetName);
}
template <typename T>
inline T LoadAsset(const std::string assetName) {
	throw std::exception(std::format("Loading unspecified asset: {}", typeid(T).name()) );
	return T();
}
template <>
inline Sound LoadAsset<Sound>(const std::string assetName) {
	return ::LoadSound( getAssetPath(assetName + ".ogg").c_str() );
}
template <>
inline Texture2D LoadAsset<Texture2D>(const std::string assetName) {
	return ::LoadTexture( getAssetPath(assetName + ".png").c_str() );
}
template <>
inline Font LoadAsset<Font>(const std::string assetName) {
	return ::LoadFont( getAssetPath(assetName + ".ttf").c_str() );
}

inline void UnloadAsset(Texture2D& texture) { UnloadTexture(texture); }
inline void UnloadAsset(Sound& sound) { UnloadSound(sound); }
inline void UnloadAsset(Font& font) { UnloadFont(font); }


template <typename T>
struct Asset {
	static_assert(std::is_base_of<Texture2D, T>() || std::is_base_of<Sound, T>() || std::is_base_of<Font, T>());
	Asset(std::string name) { _asset = std::make_unique<T>(LoadAsset<T>(name)); }
	~Asset() { UnloadAsset(getAsset());}

	T& getAsset() const noexcept { return *_asset; }
	protected:
	std::unique_ptr<T> _asset;
};

using texture_map = std::unordered_map<std::string, Texture2D>;
using sound_map = std::unordered_map<std::string, Sound>;
using font_map = std::unordered_map<std::string, Font>;


template <class AssetType>
class AssetPack {
	static_assert(std::is_base_of<Texture2D, AssetType>() || std::is_base_of<Sound, AssetType>() || std::is_base_of<Font, AssetType>());
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
	std::vector<std::string> names = {"Alien", "Barrier", "Laser", "Ship1", "Ship2", "Ship3"};
	texture_map textures;

	public:
	Texture2D& getTexture(std::string textureName) {
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
			return;
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
	std::string soundNames[1] = { "hitHurt"}; //should load from file
	sound_map sounds;

	public:
	Sound& getSound(std::string soundName) {
		if(!sounds.contains(soundName)) {
			throw std::runtime_error(std::format("Sound {} not found.", soundName));
		}
		return sounds[soundName];
	}
};
using SoundPack = AssetPack<Sound>;

