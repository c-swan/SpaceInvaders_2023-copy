#pragma once 
#include <iostream>
#include <string>
#include <fstream>
#include <raylib.h>

struct Entity
{
	Vector2 position;

	void LoadLevelFromAFile(const std::string& filename); //why not free function?
};
