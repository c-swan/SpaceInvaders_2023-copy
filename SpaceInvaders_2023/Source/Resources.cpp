#include "Resources.h"
#include <iostream>
#include <print>

void Resources::Load()
{
	alienTexture = LoadTexture("./Assets/Alien.png"); //change ".Assets/" to constant...
	barrierTexture = LoadTexture("./Assets/Barrier.png");
	shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));
	laserTexture = LoadTexture("./Assets/Laser.png");
}
/* //TODO: destructor!!!!!, unload all textures
void Resources::Unload()
{
	UnloadTexture(barrierTexture);
	UnloadTexture(alienTexture);
}
*/
