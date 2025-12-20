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
		hitSound = LoadSound("./Assets/hitHurt.ogg");
	}
	~Sounds() {
		UnloadSound(hitSound);
		CloseAudioDevice();
	}
	void playHitSound() {  PlaySound(hitSound); }
	private:
		Sound hitSound;
};
#endif /* Sounds_h */
