//
//  GameState.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#include "GameState.hpp"
#include <raylib.h>

void enter(const Game &game) {}
void exit(const Game &game) {}
static GameState& getInstance();

void StartScreen::Render() {
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void StartScreen::Update() {
	if (IsKeyReleased(KEY_SPACE))
	{
		setState(Gameplay::getInstance())
	}
}

void Gameplay::Render() {
	//background render LEAVE THIS AT TOP
	background.Render();

	//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	//player rendering
	player.Render(resources.shipTextures[player.activeTexture]);

	//projectile rendering
	for (int i = 0; i < Projectiles.size(); i++)
	{
		Projectiles[i].Render(resources.laserTexture);
	}

	// wall rendering
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i].Render(resources.barrierTexture);
	}

	//alien rendering
	for (int i = 0; i < Aliens.size(); i++)
	{
		Aliens[i].Render(resources.alienTexture);
	}
}

void EndScreen::Render() {
	//Code
	//DrawText("END", 50, 50, 40, YELLOW);

	if (newHighScore)
	{
		DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);



		// BELOW CODE IS FOR NAME INPUT RENDER
		DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText)
		{
			// HOVER CONFIRMIATION
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		}
		else
		{
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
		}

		//Draw the name being typed out
		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		//Draw the text explaining how many characters are used
		DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

		if (mouseOnText)
		{
			if (letterCount < 9)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0)
				{
					DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
				}

			}
			else
			{
				//Name needs to be shorter
				DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
			}

		}

		// Explain how to continue when name is input
		if (letterCount > 0 && letterCount < 9)
		{
			DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
		}

	}
	else {
		// If no highscore or name is entered, show scoreboard and call it a day
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

		DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

		for (int i = 0; i < Leaderboard.size(); i++)
		{
			char* tempNameDisplay = Leaderboard[i].name.data();
			DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
			DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
		}
	}

}
GameState& StartScreen::getInstance() { static StartScreen singleton; return singleton; }
GameState& Gameplay::getInstance() { static Gameplay singleton; return singleton; }
GameState& EndScreen::getInstance() { static EndScreen singleton; return singleton; }
