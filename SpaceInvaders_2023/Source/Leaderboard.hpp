#pragma once
#include <string>
#include <vector>

#include "Constants.hpp"
#include "ErrorHandling.hpp"
#include "Renderer.hpp"

struct PlayerData {
	std::string name;
	int score;
};

class Leaderboard {
public:
	Leaderboard() : titleText("LEADERBOARD", LEADERBOARD_POSITION) { LoadDummyScores(); /*LoadFromFile();*/ }
	~Leaderboard() { SaveToFile(); }

	std::optional<ErrorType> LoadFromFile() { return LoadFromFile(LEADERBOARD_PATH); LoadText(); }
	std::optional<ErrorType> SaveToFile() { return SaveToFile(LEADERBOARD_PATH); }
	std::optional<ErrorType> LoadFromFile(const std::string& pathName);
	std::optional<ErrorType> SaveToFile(const std::string& pathName);

	void LoadText();
	void Render(Renderer& renderer);
	bool CheckNewHighscore(int score) { return (score > highscores.back().score); }
	void InsertNewHighscore(const std::string& name, int score);
	void LoadDummyScores() noexcept {
		highscores = {
			{"Player 1", 500},
			{"Player 2", 400},
			{"Player 3", 300},
			{"Player 4", 200},
			{"Player 5", 100}
		};
		LoadText();
	}

private:
	std::vector<PlayerData> highscores;

	TextUI titleText;
	std::vector<TextUI> text;
};

