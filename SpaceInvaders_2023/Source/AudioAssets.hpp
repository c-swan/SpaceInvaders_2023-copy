#pragma once
#include "Constants.h"
#include <raylib.h>

class AudioAssets {
public:
	AudioAssets() {
		InitAudioDevice();
		sound = LoadSound("./hitHurt.ogg");
	}
	~AudioAssets() {
		CloseAudioDevice();
	}

	Sound sound;

	AudioAssets(const AudioAssets&) = delete;
	AudioAssets(AudioAssets&&) = delete;
	AudioAssets& operator=(const AudioAssets&) = delete;
	AudioAssets& operator=(AudioAssets&&) = delete;
};
