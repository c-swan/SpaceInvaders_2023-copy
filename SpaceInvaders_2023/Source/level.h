#pragma once 
#include <iostream>
#include <string>
#include <fstream>

struct Entity //TODO: unused
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);
};
