#pragma once
#include <string>
#include <vector>
#include <optional>
#include <raylib.h>

struct Entity {
	Vector2 position;
	float x, y;
};

std::optional<std::vector<Entity>>  LoadEntityFromFile(const std::string& filename);
