//
//  Leaderboard.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#include "Leaderboard.hpp"
#include <fstream>
#include <print>
#include "Constants.h"

Leaderboard::Leaderboard() {

}

Leaderboard::~Leaderboard() {

}
void Leaderboard::SaveToFile() {

	// SAVE LEADERBOARD AS ARRAY //clarification...?
	/*
	 {
	 "Leaderboard" : [
	 { "name":"Player 1", "score":2000 },
	 { "name":"Player 2", "score":1000 },
	 { "name":"Player 3", "score":500 },
	 { "name":"Player 4", "score":200 },
	 { "name":"Player 5", "score":100 },
	 ]
	 }
	 */

	// OPEN FILE
	std::ofstream file; //fstream -> ofstream, to create file if doesn't exist

	file.open("./Leaderboard.txt"); //use relative path and txt extension, why not

	if (!file) {
		std::println("file not found!");
	}
	else {
		std::println("file found!");
	}

	

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}


void Leaderboard::LoadFromFile() {

	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}



void Leaderboard::Render() {

	DrawText("LEADERBOARD", 50, 100, DEFAULT_FONT_SIZE, TEXT_COLOR);

	int i=0;
	for(auto &entry : playerData) {
		char* tempNameDisplay = entry.name.data();
		DrawText(tempNameDisplay, 50, 140 + (i * 40), DEFAULT_FONT_SIZE, TEXT_COLOR);
		DrawText(TextFormat("%i", entry.score), 350, 140 + (i * 40), DEFAULT_FONT_SIZE, TEXT_COLOR);
		i++;
	}
}

bool Leaderboard::CheckNewHighScore(int score) {
	return (score > playerData[4].score); //return this
}


void Leaderboard::InsertNewHighScore(std::string name, int score) {
	PlayerData newData{name, score};

	for (int i = 0; i < playerData.size(); i++) { //
		if (newData.score > playerData[i].score) {
			playerData.insert(playerData.begin() + i, newData);
			playerData.pop_back();
			return;
		}
	}
}
