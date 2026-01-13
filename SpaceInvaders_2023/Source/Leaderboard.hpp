#pragma once

#include <string>
#include <vector>
#include "Constants.h"
#include "Math.h"
#include "ErrorHandling.h"
#include "Renderer.h"

struct PlayerData {
	std::string name;
	int score;
};

class Leaderboard {
public:
	Leaderboard() { LoadDummyScores(); /*LoadFromFile();*/ }
	~Leaderboard() { SaveToFile(); }

	std::optional<ErrorType> LoadFromFile() { return LoadFromFile(LEADERBOARD_PATH); }
	std::optional<ErrorType> SaveToFile() { return SaveToFile(LEADERBOARD_PATH); }
	std::optional<ErrorType> LoadFromFile(const std::string& pathName);
	std::optional<ErrorType> SaveToFile(const std::string& pathName);

	void Render();
	bool CheckNewHighscore(int score) { return (score > highscores.back().score); }
	void InsertNewHighscore(const std::string& name, int score);
	void ClearHighscore() { highscores.clear(); }
	void LoadDummyScores() noexcept {
		highscores = {
			{"Player 1", 500},
			{"Player 2", 400},
			{"Player 3", 300},
			{"Player 4", 200},
			{"Player 5", 100}
		};
	}

private:
	std::vector<PlayerData> highscores;
//	Vector2 position {LEADERBOARD_POSITION_X, LEADERBOARD_POSITION_Y};

};

