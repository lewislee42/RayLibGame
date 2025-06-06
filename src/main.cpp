
#include "Components.h"
#include "raylib/raymath.h"
#include <raylib/raylib.h>
#include <string>
#include <iostream>

#include <Player.h>
#include <AssetsManager.h>
#include <ObjectsManager.h>
#include <Entity.h>
#include <Game.h>

#include <cstdlib>


/* ---------------- PRINTING OUT UI ---------------- */
void	DrawVector(std::string text, const Vector3 &vec, const uint &x, const uint &y) {
	text += ": x " + std::to_string(vec.x);
	text += ", y " + std::to_string(vec.y);
	text += ", z " + std::to_string(vec.z);
	DrawText(text.c_str(), x, y, 10, BLACK);
}

void	DrawUI(entt::registry &registry) {
	auto view = registry.view<PlayerTag>();

	entt::entity player = *view.begin();
	Camera3D& camera = registry.get<CameraComponent>(player);
	Vector3& direction = registry.get<Direction>(player);
	Vector3& velocity = registry.get<Velocity>(player);

	DrawFPS(10, 10);
	DrawVector("position", camera.position, 10, 40);
	DrawVector("direction", direction, 10, 50);
	DrawVector("velocity", velocity, 10, 60);
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

void	generateRandomBlocks(ObjectsManager &objectsManager, AssetsManager &assetsManager) {
	for (int i = 0; i < 100; i++) {
		float x = -50 + (50 - -50) * ((double)rand() / (double(RAND_MAX) + 1)); // the -+ 50 is to keep it within the red platform
		float z = -50 + (50 - -50) * ((double)rand() / (double(RAND_MAX) + 1));
		float y = 1;

		float randomNumber = ((double)rand() / (double(RAND_MAX) + 1));
		
		Color color = randomColor();
		std::string assetName;

		if (randomNumber < 0.25)
			assetName = "BLOCK_0";
		else if (randomNumber < 0.5)
			assetName = "BLOCK_1";
		else if (randomNumber < 0.75)
			assetName = "BLOCK_2";
		else
			assetName = "BLOCK_3";

		
		objectsManager.objects.push_back(
			new Object(
				assetsManager.models[assetName],
				Vector3{x, y, z},
				color,
				Vector3{0.0f, 0.0f, 1.0f}
			)
		);
	}
}

// could be done better
void	HandlePlayerKeyboardInput(entt::registry &registry) {
	auto view = registry.view<PlayerTag, Velocity, CameraComponent, Speed, IsGrounded, Direction>();
	for (auto entity : view) {
		Vector3& velocity	= registry.get<Velocity>(entity);
		Camera3D& camera	= registry.get<CameraComponent>(entity);
		float& speed		= registry.get<Speed>(entity);
		bool& isGrounded	= registry.get<IsGrounded>(entity);
		Vector3& direction	= registry.get<Direction>(entity);
	
		direction = Vector3Subtract(camera.target, camera.position);
		Vector3 forward = Vector3Normalize(direction);
		forward.y = 0;
		if (Vector3LengthSqr(forward) > 0.001) {
			forward = Vector3Normalize(forward);
		}
		else {
			forward = Vector3{0.0f, 0.0f, 1.0f};
		}

		velocity.x = 0;
		velocity.z = 0;

		Vector3 right = Vector3CrossProduct(forward, camera.up);
		right = Vector3Normalize(right);

		/* ---- Handle WASD ---- */
		if (IsKeyDown(KEY_W)) {
			velocity = Vector3Add(velocity, Vector3Scale(forward, speed));
		}
		if (IsKeyDown(KEY_S)) {
			velocity = Vector3Subtract(velocity, Vector3Scale(forward, speed));
		}
		if (IsKeyDown(KEY_D)) {
			velocity = Vector3Add(velocity, Vector3Scale(right, speed));
		}
		if (IsKeyDown(KEY_A)) {
			velocity = Vector3Subtract(velocity, Vector3Scale(right, speed));
		}

		/* ---- Handle jumping ---- */
		if (IsKeyDown(KEY_SPACE) && isGrounded) {
			velocity.y += 5;
			isGrounded = false;
		}
	}
}

void	ApplyGravity(entt::registry &registry, const float &deltaTime) {
	auto view = registry.view<Velocity, Gravity>();
	for (auto entity : view) {
		Vector3& velocity		= registry.get<Velocity>(entity);
		float& gravity		= registry.get<Gravity>(entity);

		auto *isGrounded	= registry.try_get<IsGrounded>(entity);
		if (isGrounded) {
			if (isGrounded->isGrounded == false)
				velocity.y += -gravity * deltaTime;
		}
		else {
			velocity.y += -gravity * deltaTime;
		}
	}
}

void	HandlePlayerMouseInput(entt::registry &registry) {
	auto view = registry.view<PlayerTag, MouseInput, Velocity, CameraComponent, Direction>(); // hard code using camera component as of now
	for (auto entity : view) {
		Camera3D& camera		= registry.get<CameraComponent>(entity);
		float& mouseSensitivity	= registry.get<MouseInput>(entity);
		Vector3& direction		= registry.get<Direction>(entity);

		Vector2 mouseDelta = GetMouseDelta();
		Vector3 currentLookDirection = Vector3Normalize(direction);

		Vector3 yawAxis = { 0.0f, 1.0f, 0.0f };
		float yawAngle = -mouseDelta.x * mouseSensitivity;
		currentLookDirection = Vector3RotateByAxisAngle(currentLookDirection, yawAxis, yawAngle * DEG2RAD);

		Vector3 localRight = Vector3CrossProduct(currentLookDirection, camera.up);
		localRight = Vector3Normalize(localRight);
		float pitchAngle = -mouseDelta.y * mouseSensitivity;
		currentLookDirection = Vector3RotateByAxisAngle(currentLookDirection, localRight, pitchAngle * DEG2RAD);

		currentLookDirection = Vector3Normalize(currentLookDirection);
		camera.target = Vector3Add(camera.position, currentLookDirection);
	}
}

void	UpdatePosition(entt::registry &registry, float deltaTime) {
	auto view = registry.view<Velocity>();
	for (auto entity : view) {
		Vector3& velocity			= registry.get<Velocity>(entity);
		BoundingBox& boundingBox	= registry.get<CollisionBox>(entity);
		Position *position			= registry.try_get<Position>(entity);

		if (position) { // idk what to do here
			position->position = Vector3Add(*position, Vector3Scale(velocity, deltaTime));
			continue;
		}

		CameraComponent *camera		= registry.try_get<CameraComponent>(entity);
		if (camera) {
			camera->camera.position = Vector3Add(camera->camera.position, Vector3Scale(velocity, deltaTime));
		}
	}
}


/* ---------------- MAIN LOOP ---------------- */
int main() {
	// Initialization
	int windowWidth = 1200;
	int windowHeight = 700;

	InitWindow(windowWidth, windowHeight, "Testing window");

	Player player;
	Game	game;

	AssetsManager assetsManager;
	ObjectsManager objectsManager;

	/* ---- GENERATES FLOOR ---- */
	objectsManager.objects.push_back(
		new Object(
			assetsManager.models["GROUND"],
			Vector3{0, 0, 0},
			GRAY,
			Vector3{0.0f, 0.0f, 1.0f}
		)
	);
	
	generateRandomBlocks(objectsManager, assetsManager);

	SetTargetFPS(120);
	DisableCursor();

	while (!WindowShouldClose()) {
	auto view = game.registry.view<CameraComponent, Velocity>();
	auto entity = *view.begin();
	Camera3D &camera = game.registry.get<CameraComponent>(entity);
	Velocity &velocity = game.registry.get<Velocity>(entity);

		// Handles Input
		float dt = GetFrameTime();
		player.updatePlayer(dt, objectsManager, assetsManager);
		HandlePlayerKeyboardInput(game.registry);
		/*ApplyGravity(game.registry, dt);*/
		UpdatePosition(game.registry, dt);
		HandlePlayerMouseInput(game.registry);

		objectsManager.updateEntities(dt);
		
		// Preps for Drawing
		ClearBackground(WHITE);
		BeginDrawing();

		BeginMode3D(camera);

			// Draws
			objectsManager.renderObjects();
			objectsManager.renderEntities();

		EndMode3D();

		/* ---- Drawing UI ---- */
		DrawUI(game.registry);

		EndDrawing();
	}

	// Clean up
	CloseWindow();
	return 0;
}


