#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "level.h"
#include "Math.hpp"

void spawn(Entity &entity) {
	std::println("Spawn entity at {}", entity.position);
}

void LoadLevelFromFile(const std::string& filename)  //TODO: unused, implement or remove
{
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::println("Unable to open file: {}", filename);
		return;
	}

	std::vector<Entity> entities;
	float x, y;

	while (file >> x >> y)
	{
		Entity entity(x,y);
		entities.push_back(entity);
	}

	file.close();

	for(auto &entity : entities) {
		spawn(entity);
	}

}
