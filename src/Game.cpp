
#include <Game.h>

Game::Game() {

	// init player
	entt::entity player = registry.create();
	registry.emplace<Velocity>(player, Vector3{0.0f, 0.0f, 0.0f});
	registry.emplace<Direction>(player, Vector3{0.0f, 0.0f, 1.0f});
	registry.emplace<CameraComponent>(player, Vector3{0.0f, 1.1f, 0.0f});
	registry.emplace<Speed>(player, 9.0f);
	registry.emplace<MouseInput>(player, 0.4f);
	registry.emplace<Gravity>(player, 15.0f);
	registry.emplace<IsGrounded>(player, false);
	registry.emplace<Size>(player, 1.0f, 1.0f, 1.0f);

	Size& playerSize = registry.get<Size>(player);
	CameraComponent& playerCamera = registry.get<CameraComponent>(player);
	registry.emplace<CollisionBox>(player, (BoundingBox){
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

	registry.emplace<KeyboardInputTag>(player);
	registry.emplace<PlayerTag>(player);
}

Game::~Game() {}
