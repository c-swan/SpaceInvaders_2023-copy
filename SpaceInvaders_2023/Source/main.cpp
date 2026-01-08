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

int main(void) {
	Game game; //game constructor called
	game.Launch();
	// Main game loop
	while (!WindowShouldClose()) {// Detect window close button or ESC key
		//game.playSounds(); -> move to Update or delete
		game.Update();
		game.Draw();
	}
	//Game destructor called
	std::string filename = "level.txt";
	return 0;
}
