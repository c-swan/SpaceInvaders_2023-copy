#include "Leaderboard.hpp"

#include <fstream>
#include <format>
#include <string>
#include <ranges>
#include <exception>

using std::string;

std::optional<ErrorType> Leaderboard::SaveToFile(const string& pathName) {
	std::ofstream file; //fstream -> ofstream, to create file if doesn't exist
	file.open(pathName); //use relative path and txt extension, why not

	if (!file) {
		throw ErrorType::FILE_COULD_NOT_OPEN;
	}
	if (!file.is_open()) {
		throw ErrorType::FILE_COULD_NOT_OPEN; //std::runtime_error("Could not open file: " + pathName);
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
		text.emplace_back(TextUI(entry.name, LEADERBOARD_POSITION + Vector2(0, i * DEFAULT_FONT_SIZE)));
		text.emplace_back(TextUI(std::to_string(entry.score), LEADERBOARD_POSITION + Vector2(LEADERBOARD_SCORE_COLUMN, i * DEFAULT_FONT_SIZE)));
		i++;
	}
}

void Leaderboard::InsertNewHighscore(const string& name, int score) {
	auto checkNewHighscore = [score](PlayerData& entry) { return score > entry.score; };
	auto insert_pos = std::ranges::find_if(highscores, checkNewHighscore);
	if(insert_pos == highscores.end()) {
		return;
	}
	highscores.insert(insert_pos, {name, score});
	highscores.pop_back();
	LoadText();
}
