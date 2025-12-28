//
//  Leaderboard.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//
#include "Constants.h"
#include "Render.h"
#include "Leaderboard.hpp"
#include "ErrorHandling.h"

#include <fstream>
#include <print>
#include <format>
#include <string>
#include <expected>

using std::string;

std::optional<ErrorType> Leaderboard::SaveToFile(const string& pathName) {

	std::ofstream file; //fstream -> ofstream, to create file if doesn't exist
	file.open(pathName); //use relative path and txt extension, why not

	if (!file) {
		return ErrorType::MISSING_FILE;
	}

	file << "{\n" << "\"Leaderboard\" : [\n";
	for(auto& entry : highscores) {
		//{ "name":"Player 1", "score":2000 },
		file << "{ " << std::format("\"name\":\"{}\", \"score\":{}", entry.name, entry.score) << " },\n";
	}
	file << "]\n}";

	file.close();
	return {};
}


std::optional<ErrorType> Leaderboard::LoadFromFile(const string &fileName) {

	std::ifstream file;

	// READ DATA

	highscores.clear();

	// WRITE DATA ONTO LEADERBOARD

	file.close();
	return {};
}

void Leaderboard::Render() {
	Render::DrawText("LEADERBOARD", bounds);
	int i=1;
	for(auto &entry : highscores) {
		Render::DrawText(entry.name, bounds + Vector2(0, i * DEFAULT_FONT_SIZE));
		Render::DrawText(std::to_string(entry.score), bounds + Vector2(LEADERBOARD_SCORE_COLUMN, i * DEFAULT_FONT_SIZE));
		i++;
	}
}

void Leaderboard::InsertNewHighscore(const string& name, int score) {
//	PlayerData newData{name, score};

	auto highscoreCheck = [score](PlayerData& entry) { return score > entry.score; };
	auto insert_pos = std::find_if(highscores.begin(), highscores.end(), highscoreCheck);
	if(insert_pos == highscores.end()) return;
	highscores.insert(insert_pos, PlayerData(name, score));
/*
	for (int i = 0; i < highscores.size(); i++) {
		if (score > highscores[i].score) {
			highscores.insert(highscores.begin() + i, PlayerData(name, score));
			highscores.pop_back();
			return;
		}
	}
 */
}
