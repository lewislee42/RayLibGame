
#include <raylib.h>
#include <string>
#include <iostream>

#include <Player.h>
#include <ObjectsManager.h>
#include <Entity.h>

#include <cstdlib>


/* ---------------- PRINTING OUT UI ---------------- */
void	DrawVector(std::string text, const Vector3 &vec, const uint &x, const uint &y) {
	text += ": x " + std::to_string(vec.x);
	text += ", y " + std::to_string(vec.y);
	text += ", z " + std::to_string(vec.z);
	DrawText(text.c_str(), x, y, 10, BLACK);
}

void	DrawUI(const Player &player) {
	DrawFPS(10, 10);
	DrawVector("position", player.camera.position, 10, 40);
	DrawVector("target", player.camera.target, 10, 50);
	DrawVector("velocity", player.getVelocity(), 10, 60);
}


/* ---------------- GENERATING WORLD ---------------- */
Color	randomColor() {
	float n = ((double)rand() / (double(RAND_MAX) + 1));

	if (n < 0.1)
		return RED;
	else if (n < 0.2)
		return GREEN;
	else if (n < 0.3)
		return BLUE;
	else if (n < 0.4)
		return GOLD;
	else if (n < 0.5)
		return BROWN;
	else if (n < 0.6)
		return VIOLET;
	else if (n < 0.7)
		return PINK;
	else if (n < 0.8)
		return LIME;
	else if (n < 0.9)
		return DARKBLUE;
	else
		return BLACK;
}

void	generateRandomBlocks(ObjectsManager &objectsManager) {
	for (int i = 0; i < 100; i++) {
		float width = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));
		float height = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));
		float length = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));

		float x = -50 + (50 - -50) * ((double)rand() / (double(RAND_MAX) + 1)); // the -+ 50 is to keep it within the red platform
		float y = 5 * ((double)rand() / (double(RAND_MAX) + 1));
		float z = -50 + (50 - -50) * ((double)rand() / (double(RAND_MAX) + 1));
		
		Color color = randomColor();
		
		objectsManager.objects.push_back(
			new Object(
				LoadModelFromMesh(GenMeshCube(width, height, length)),
				Vector3{x, y, z},
				color,
				1,
				Vector3{0.0f, 0.0f, 1.0f}
			)
		);
	}
}


/* ---------------- MAIN LOOP ---------------- */
int main() {
	// Initialization
	int windowWidth = 1200;
	int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "Testing window");

	Player player;
	ObjectsManager objectsManager;

	/* ---- GENERATES FLOOR ---- */
	objectsManager.objects.push_back(
		new Object(
			LoadModelFromMesh(GenMeshCube(100, 1, 100)),
			Vector3{0, 0, 0},
			GRAY,
			1,
			Vector3{0.0f, 0.0f, 1.0f}
		)
	);
	
	generateRandomBlocks(objectsManager);

	SetTargetFPS(120);
	DisableCursor();

	while (!WindowShouldClose()) {

		// Handles Input
		float dt = GetFrameTime();
		player.updatePlayer(dt, objectsManager);

		// tmep code
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			float width = 0.1f;
			float height = 0.1f;
			float length = 0.1f;

			float x = player.camera.position.x;
			float y = player.camera.position.y;
			float z = player.camera.position.z;
			
			Color color = randomColor();

			Entity* entity = new Entity(
				LoadModelFromMesh(GenMeshCube(width, height, length)),
				Vector3{x, y, z},
				color,
				1,
				Vector3Subtract(player.camera.target, player.camera.position),
				Vector3Normalize(Vector3Subtract(player.camera.target, player.camera.position)),
				5
			);
			objectsManager.entities.push_back(entity);
		}

		objectsManager.updateEntities(dt);
		
		// Preps for Drawing
		ClearBackground(WHITE);
		BeginDrawing();

		BeginMode3D(player.camera);

			// Draws
			objectsManager.renderObjects();
			objectsManager.renderEntities();

		EndMode3D();

		/* ---- Drawing UI ---- */
		DrawUI(player);


		EndDrawing();
	}

	// Clean up
	CloseWindow();
	return 0;
}

