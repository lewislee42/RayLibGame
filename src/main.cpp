
#include <raylib.h>
#include <string>
#include <raymath.h>
#include <vector>

#include <Player.h>


int main() {
	// Initialization
	int windowWidth = 1200;
	int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "Testing window");

	Player player;

	std::vector <Model> objects;
	std::vector <Vector3> objectsPos;
	objects.push_back(LoadModelFromMesh(GenMeshCube(1, 1, 1)));
	objectsPos.push_back(Vector3{1, 1, 1});

	SetTargetFPS(120);
	DisableCursor();

	while (!WindowShouldClose()) {

		// Handles Input
		
		float dt = GetFrameTime();

		player.updatePlayer(dt);
		

		// Preps for Drawing
		BeginDrawing();

		// Clears the screen to draw again
		ClearBackground(WHITE);

			BeginMode3D(player.camera);

			// Draws
			DrawGrid(100, 1);

			for (int i = 0; i < (int)objects.size(); i++) {
				DrawModel(objects[i], objectsPos[i], 1, RED);
			}

		EndMode3D();

		/* ----- Drawing UI ----- */

		DrawFPS(10, 10);
		std::string position("position: x ");
		position +=  std::to_string(player.camera.position.x) + ", y " + std::to_string(player.camera.position.y) + ", z " + std::to_string(player.camera.position.z);
		DrawText(position.c_str(), 10, 30, 10, BLACK);
		std::string target("target: x ");
		target += std::to_string(player.camera.target.x) + ", y " + std::to_string(player.camera.target.y) + ", z " + std::to_string(player.camera.target.z);
		DrawText(target.c_str(), 10, 40, 10, BLACK);
		EndDrawing();
	}

	// Clean up
	CloseWindow();
	return 0;
}

