

#include "Components.h"
#include "RocketSystem.h"
#include <Game.h>
#include <AssetsManager.h>


Game::Game(): assetsManager() {

	InitScene();
	InitWeapons();
	InitPlayer();
}

Game::~Game() {
}



// helper function
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

void	Game::Run() {

	while (!WindowShouldClose()) {
		auto view = registry.view<CameraComponent, Velocity>();
		auto entity = *view.begin();
		Camera3D &camera = registry.get<CameraComponent>(entity).camera;
		Vector3 &velocity = registry.get<Velocity>(entity).velocity;

		// Handles Input
		float dt = GetFrameTime();
		PlayerSystem(registry, dt, assetsManager);
		RocketSystem(registry, dt);
		

		/*objectsManager.updateEntities(dt);*/
		
		// Preps for Drawing
		ClearBackground(WHITE);
		BeginDrawing();

		BeginMode3D(camera);

			// Draws
			RenderObjects(registry);

		EndMode3D();

		/* ---- Drawing UI ---- */
		DrawUI(registry);

		EndDrawing();
	}

}

void	Game::InitPlayer() {
	entt::entity player = registry.create();
	registry.emplace<Velocity>(player, Vector3{0.0f, 0.0f, 0.0f});
	registry.emplace<Direction>(player, Vector3{0.0f, 0.0f, 1.0f});
	registry.emplace<CameraComponent>(player, Vector3{0.0f, 1.1f, 0.0f});
	registry.emplace<Speed>(player, 9.0f);
	registry.emplace<MouseInput>(player, 0.4f);
	registry.emplace<Gravity>(player, 15.0f);
	registry.emplace<IsGrounded>(player, false);
	registry.emplace<Dimensions>(player, 1.0f, 1.0f, 1.0f);
	Dimensions& playerSize = registry.get<Dimensions>(player);
	CameraComponent& playerCamera = registry.get<CameraComponent>(player);
	registry.emplace<BoundingBoxComponent>(player, (BoundingBox){
		.min = {
			playerCamera.camera.position.x - playerSize.width / 2,
			playerCamera.camera.position.y - playerSize.height / 2,
			playerCamera.camera.position.z - playerSize.depth / 2
		},
		.max = {
			playerCamera.camera.position.x + playerSize.width / 2,
			playerCamera.camera.position.y + playerSize.height / 2,
			playerCamera.camera.position.z + playerSize.depth / 2
		}
	});
	auto view = registry.view<WeaponComponent>();
	entt::entity weapon = *view.begin();
	registry.emplace<EquippedWeapon>(player, weapon);
	registry.emplace<PlayerTag>(player);
}

void	Game::InitScene() {
	entt::entity floor = registry.create();
	registry.emplace<ModelComponent>(floor, assetsManager.models["GROUND"]);
	registry.emplace<Position>(floor, Vector3{0.0f, 0.0f, 0.0f});
	registry.emplace<ColorComponent>(floor, GRAY);
	registry.emplace<Direction>(floor, Vector3{0.0f, 0.0f, 1.0f});
	Model &model = registry.get<ModelComponent>(floor).model;
	Vector3 &position = registry.get<Position>(floor).position;
	BoundingBox floorBoundingBox = GetMeshBoundingBox(model.meshes[0]);

	for (int i = 1; i < model.meshCount; i++) {
		BoundingBox meshBoundingBox = GetMeshBoundingBox(model.meshes[i]);

		floorBoundingBox.min.x = fminf(floorBoundingBox.min.x, meshBoundingBox.min.x);
		floorBoundingBox.min.y = fminf(floorBoundingBox.min.y, meshBoundingBox.min.y);
		floorBoundingBox.min.z = fminf(floorBoundingBox.min.z, meshBoundingBox.min.z);


		floorBoundingBox.max.x = fminf(floorBoundingBox.max.x, meshBoundingBox.max.x);
		floorBoundingBox.max.y = fminf(floorBoundingBox.max.y, meshBoundingBox.max.y);
		floorBoundingBox.max.z = fminf(floorBoundingBox.max.z, meshBoundingBox.max.z);
	}
	BoundingBox floorBoundingBoxWS = {
		.min = Vector3Add(floorBoundingBox.min, position),
		.max = Vector3Add(floorBoundingBox.max, position)
	};
	registry.emplace<BoundingBoxComponent>(floor, floorBoundingBoxWS);
	registry.emplace<ObjectTag>(floor);
	

	for (int i = 0; i < 100; i++) {
		float x = -50 + (50 - -50) * ((double)rand() / (double(RAND_MAX) + 1)); // the -+ 50 is to keep it within the floor
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

		entt::entity object = registry.create();
		registry.emplace<ModelComponent>(object, assetsManager.models[assetName]);
		registry.emplace<Position>(object, Vector3{x, y, z});
		registry.emplace<ColorComponent>(object, color);
		registry.emplace<Direction>(object, Vector3{0.0f, 0.0f, 1.0f});
		Model &objectModel = registry.get<ModelComponent>(object).model;
		Vector3 &objectPosition = registry.get<Position>(object).position;
		BoundingBox boundingBox = GetMeshBoundingBox(objectModel.meshes[0]);

		for (int i = 1; i < objectModel.meshCount; i++) {
			BoundingBox meshBoundingBox = GetMeshBoundingBox(objectModel.meshes[i]);

			boundingBox.min.x = fminf(boundingBox.min.x, meshBoundingBox.min.x);
			boundingBox.min.y = fminf(boundingBox.min.y, meshBoundingBox.min.y);
			boundingBox.min.z = fminf(boundingBox.min.z, meshBoundingBox.min.z);


			boundingBox.max.x = fminf(boundingBox.max.x, meshBoundingBox.max.x);
			boundingBox.max.y = fminf(boundingBox.max.y, meshBoundingBox.max.y);
			boundingBox.max.z = fminf(boundingBox.max.z, meshBoundingBox.max.z);
		}
		BoundingBox boundingBoxWS = {
			.min = Vector3Add(boundingBox.min, objectPosition),
			.max = Vector3Add(boundingBox.max, objectPosition)
		};
		registry.emplace<Dimensions>(
			object,
			boundingBox.max.x - boundingBox.min.x,
			boundingBox.max.y - boundingBox.min.y, 
			boundingBox.max.z - boundingBox.min.z
		);
		registry.emplace<BoundingBoxComponent>(object, boundingBoxWS);
		registry.emplace<ObjectTag>(object);
	}
}

void	Game::InitWeapons() {
	entt::entity rocketLauncher = registry.create();

	registry.emplace<ModelComponent>(rocketLauncher, assetsManager.models["ROCKET_LAUNCHER"]);
	registry.emplace<WeaponComponent>(rocketLauncher, ROCKET_LAUNCHER);
}
