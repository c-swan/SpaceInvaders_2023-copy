#include "Resources.h"
#include <iostream>
#include "Constants.h"

void Resources::Load()
{
	std::cout << "Yay"; // yes
	alienTexture = LoadTexture((ASSETS_DIR + "Alien.png").c_str());
	barrierTexture = LoadTexture((ASSETS_DIR + "Barrier.png").c_str());
	shipTextures.push_back(LoadTexture((ASSETS_DIR + "Ship1.png").c_str()));
	shipTextures.push_back(LoadTexture((ASSETS_DIR + "Ship2.png").c_str()));
	shipTextures.push_back(LoadTexture((ASSETS_DIR + "Ship3.png").c_str()));
	laserTexture = LoadTexture((ASSETS_DIR + "Laser.png").c_str());
}
/*
void Resources::Unload()
{
	UnloadTexture(barrierTexture);
	UnloadTexture(alienTexture);
}
*/
//TODO: seems important – RAII
