//
//  Sounds.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef Sounds_h
#define Sounds_h
#include <raylib.h>

class Sounds {
	public:
	Sounds() {
		InitAudioDevice();  //TODO: Error handling
		if(!IsAudioDeviceReady()) throw std::exception();
		hitSound = LoadSound("hitHurt");
	}
	~Sounds() {
		UnloadSound(hitSound);
		CloseAudioDevice();
	}
	void playHitSound() { PlaySound(hitSound); }

	Sounds(const Sounds&) = delete;
	Sounds(Sounds&&) = delete;
	Sounds& operator=(const Sounds&) = delete;
	Sounds& operator=(Sounds&&) = delete;

	private:
	Sound LoadSound(const string& assetName) { return ::LoadSound(std::format("{}{}.ogg", ASSETS_DIR, assetName).c_str()); }
	Sound hitSound;
};
#endif /* Sounds_h */
