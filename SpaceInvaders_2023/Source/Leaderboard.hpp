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

struct PlayerData {
	std::string name;
	int score;
};

class Leaderboard {
public:
	Leaderboard();
	~Leaderboard();

	void LoadFromFile();
	void SaveToFile();
	void Render();
	bool CheckNewHighScore(int score);
	void InsertNewHighScore(std::string name, int score);

private:
	std::vector<PlayerData> playerData = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };


};

#endif /* Leaderboard_hpp */
