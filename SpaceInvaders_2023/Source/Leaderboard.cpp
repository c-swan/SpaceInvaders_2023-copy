#include "Leaderboard.hpp"

#include "Constants.h"
#include "ErrorHandling.h"

#include <fstream>
#include <print>
#include <format>
#include <string>
#include <expected>
#include <exception>

using std::string;

std::optional<ErrorType> Leaderboard::SaveToFile(const string& pathName) {
	std::ofstream file; //fstream -> ofstream, to create file if doesn't exist
	file.open(pathName); //use relative path and txt extension, why not

	if (!file) {
		throw std::runtime_error("Could not create file: " + pathName);
	}
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + pathName);
	}

	file << "{\n" << "\t\"Leaderboard\" : [\n";
	int i=0;
	for(auto& entry : highscores) {
		file << "\t\t{ " << std::format("\"name\":\"{}\", \"score\":{}", entry.name, entry.score);
		file << ((i == highscores.size() - 1) ? " }\n" : " },\n");
		i++;
	}
	file << "\t]\n}";

	file.close();
	return std::nullopt;
}


std::optional<ErrorType> Leaderboard::LoadFromFile(const string &fileName) {

	std::ifstream file;

	highscores.clear();

	//Reverse-engineer saving

	file.close();
	LoadText();
	return std::nullopt;
}

void Leaderboard::Render(Renderer& renderer) {
	renderer.DrawText(titleText);
	for(auto& t : text) {
		renderer.DrawText(t);
	}
}

void Leaderboard::LoadText() {
	text.clear();
	int i=1;
	for(auto &entry : highscores) {
		text.push_back(TextUI(entry.name, LEADERBOARD_POSITION + Vector2(0, i * DEFAULT_FONT_SIZE)));
		text.push_back(TextUI(std::to_string(entry.score), LEADERBOARD_POSITION + Vector2(LEADERBOARD_SCORE_COLUMN, i * DEFAULT_FONT_SIZE)));
		i++;
	}
}

void Leaderboard::InsertNewHighscore(const string& name, int score) {
	auto checkNewHighscore = [score](PlayerData& entry) { return score > entry.score; };
	auto insert_pos = std::find_if(highscores.begin(), highscores.end(), checkNewHighscore);
	if(insert_pos == highscores.end()) {
		return;
	}
	highscores.insert(insert_pos, PlayerData(name, score));
	highscores.pop_back();
	LoadText();
}
