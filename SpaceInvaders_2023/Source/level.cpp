#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <print>
#include <format>
#include "level.h"
#include "Math.hpp"
#include "ErrorHandling.h"
#include <optional>
#include "FileHandle.h"

std::optional<std::vector<Entity>> LoadEntityFromFile(const std::string& filename) {
	FileHandle file(filename);

	if(!file) {
		throw file_error("File not found", filename);
		return std::nullopt;
	}
	if (!file.is_open()) {
		throw file_error("Unable to open file", filename);
		return std::nullopt;
	}

	std::vector<Entity> entities;
	float x, y;

	while (file.getFile() >> x >> y) { //no input sanitation
		entities.push_back(Entity({x, y}));
		debug_log(std::format("Spawn entity at: ", entities.back().position));
		if(file.fail()) {
			throw file_error("Failed to read entities from file: ", filename);
			return std::nullopt;
		}
	}
	return entities;
}



