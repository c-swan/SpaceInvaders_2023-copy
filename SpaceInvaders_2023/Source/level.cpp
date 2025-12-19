#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "level.h"
#include <raylib.h>
#include <print>

void LoadLevelFromFile(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::println("Unable to open file: {}", filename);
		return;
	}

	std::vector<Entity> entities;
	Vector2 vec;
	//float x, y; //looks a whole lot like a vector

	while (file >> vec.x >> vec.y) //read positions,
	{
		Entity entity { vec };
		entities.push_back(entity);
	}

	file.close();

	for(auto &entity : entities)
	{
		std::println("Spawn entity at ({}, {})", entity.position.x, entity.position.y);
		//std::cout << "Spawn entity at X:" << entity.position.x << ",Y:" << entity.position.y << std::endl;
	}

}
