#pragma once 
#include <iostream>
#include <string>
#include <fstream>
#include "Math.hpp"

struct Entity { //TODO: unused, implement?
	explicit Entity() : position(point{0,0}) {}
	explicit Entity(float x, float y) : position(point(x, y)) {}
	
	point position;
};

void spawn(Entity &entity);
void LoadLevelFromFile(const std::string& filename); //should be constructor...
