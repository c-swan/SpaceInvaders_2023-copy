/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *b
 *   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "game.h"
#include "Constants.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SPACE INVADERS"); //TODO: RAII, move to Window

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	Game game = { State::STARTSCREEN };
	Resources resources;
	game.resources = resources;
	game.Launch();

	//--------------------------------------------------------------------------------------

	InitAudioDevice();  //TODO: RAII, delegate to Audio class

	auto sound = LoadSound("./hitHurt.ogg");


	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		//if (IsKeyPressed(KEY_SPACE))
		//{
		//    PlaySound(sound);
		//}

		//if (IsKeyPressed(KEY_BACKSPACE))
		//{
		//    StopSound(sound);
		//}

		game.Update();

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(BLACK); //TODO: delegate to Game

		game.Render();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	CloseAudioDevice(); //delegate to Audio class

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context, delegate to Window wrapper
	//--------------------------------------------------------------------------------------

	std::string filename = "level.txt";		//unused...?

	return 0;
}
