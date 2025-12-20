#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "level.h"
#include "Math.hpp"

void LoadLevelFromFile(const std::string& filename)  //TODO: unused, implement or remove
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::vector<Entity> entities;
		float x, y;

		while (file >> x >> y)
		{
			Entity entity;
			entity.x = x;
			entity.y = y;
			entities.push_back(entity);
		}

		file.close();

		for (int i = 0; i < entities.size(); i++)
		{
			const Entity& entity = entities[i];
			std::println("Spawn entity at {}", Vector2(entity.x, entity.y));
		}
	}
	else
	{
		std::println("Unable to open file: {}", filename);
	}
}



