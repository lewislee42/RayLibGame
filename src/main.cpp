
#include <raylib/raylib.h>
#include <string>
#include <iostream>

#include <Game.h>


/* ---------------- MAIN LOOP ---------------- */
int main() {
	// Initialization
	int windowWidth = 1200;
	int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "Testing window");
	SetTargetFPS(120);
	DisableCursor();

	Game	game;
	game.Run();
	
	// Clean up
	CloseWindow();
	return 0;
}


