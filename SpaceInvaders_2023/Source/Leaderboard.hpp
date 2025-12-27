//
//  Leaderboard.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef Leaderboard_hpp
#define Leaderboard_hpp
#include <string>
#include <vector>
#include "Constants.h"
#include "Math.hpp"
#include "ErrorHandling.h"

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
	Rectangle bounds {LEADERBOARD_POSITION_X, LEADERBOARD_POSITION_Y, 0, 0 };

};

#endif /* Leaderboard_hpp */
