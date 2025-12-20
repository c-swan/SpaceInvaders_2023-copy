#pragma once 
#include <iostream>
#include <string>
#include <fstream>

struct Entity //TODO: unused
{
	float x, y; //Vector2 position;

	void LoadLevelFromAFile(const std::string& filename); //should be constructor...
};
