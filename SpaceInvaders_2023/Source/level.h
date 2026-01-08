#pragma once 
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Entity
{
	float x, y;

	void LoadLevelFromAFile(const std::string& filename);
};

