#pragma once
#include "raylib.h"
#include "vector"

struct Resources  //change to wrapper class, RAII
{
	void Load(); //constructor...
	//void Unload(); //we DO need this

	std::vector<Texture2D> shipTextures; //does not need to be vector, has const size
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;
};
