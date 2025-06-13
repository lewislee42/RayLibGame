

#include "raylib/raylib.h"
#include <PlayerSystem.h>


# include <iostream>
void	HandlePlayerKeyboardInput(entt::registry &registry, const entt::entity &player) {
	Movement& movement	= registry.get<Movement>(player);
	Camera3D& camera	= registry.get<CameraComponent>(player).camera;
	bool& isGrounded	= registry.get<IsGrounded>(player).isGrounded;
	Vector3& direction	= registry.get<Direction>(player).direction;

	direction = Vector3Subtract(camera.target, camera.position);
	Vector3 forward = Vector3Normalize(direction);
	forward.y = 0;
	if (Vector3LengthSqr(forward) > 0.001) {
		forward = Vector3Normalize(forward);
	}
	else {
		forward = Vector3{0.0f, 0.0f, 1.0f};
	}

	movement.velocity.x = 0;
	movement.velocity.z = 0;

	Vector3 right = Vector3CrossProduct(forward, camera.up);
	right = Vector3Normalize(right);

	/* ---- Handle WASD ---- */
	if (IsKeyDown(KEY_W)) {
		movement.velocity = Vector3Add(movement.velocity, Vector3Scale(forward, movement.speed));
	}
	if (IsKeyDown(KEY_S)) {
		movement.velocity = Vector3Subtract(movement.velocity, Vector3Scale(forward, movement.speed));
	}
	if (IsKeyDown(KEY_D)) {
		movement.velocity = Vector3Add(movement.velocity, Vector3Scale(right, movement.speed));
	}
	if (IsKeyDown(KEY_A)) {
		movement.velocity = Vector3Subtract(movement.velocity, Vector3Scale(right, movement.speed));
	}

	/* ---- Handle jumping ---- */
	if (IsKeyDown(KEY_SPACE) && isGrounded) {
		movement.velocity.y += 5;
		isGrounded = false;
	}
}

void	HandlePlayerMouseDirectionInput(entt::registry &registry, const entt::entity &player) {
	Camera3D& camera		= registry.get<CameraComponent>(player).camera;
	float& mouseSensitivity	= registry.get<MouseInput>(player).mouseSensitivity;
	Vector3& direction		= registry.get<Direction>(player).direction;

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

void	HandlePlayerMouseClickingInput(entt::registry &registry, const entt::entity &player) {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (!registry.all_of<FiringTag>(player)) {
			registry.emplace<FiringTag>(player);
		}
	} else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		if (registry.all_of<FiringTag>(player)) {
			registry.erase<FiringTag>(player);
		}
	}
}

void	UpdatePlayerPosition(entt::registry &registry, const entt::entity &player, const float &deltaTime) {
	Vector3 newPosition;
	Vector3 currentPosition;
	Movement& movement			= registry.get<Movement>(player);
	if (movement.velocity.x == 0 && movement.velocity.y == 0 && movement.velocity.z == 0)
		return ;


	Camera3D &camera			= registry.get<CameraComponent>(player).camera;
	currentPosition = camera.position;
	newPosition = Vector3Add(camera.position, Vector3Scale(movement.velocity, deltaTime));

	
	IsGrounded *isGrounded		= registry.try_get<IsGrounded>(player);
	Gravity *gravity			= registry.try_get<Gravity>(player);
	if (isGrounded && gravity) {
		if (isGrounded->isGrounded == false)
			movement.velocity.y += -gravity->gravity * deltaTime;
	}

	Dimensions& dimensions						= registry.get<Dimensions>(player);
	BoundingBoxComponent &boundingBoxComponent	= registry.get<BoundingBoxComponent>(player);
	for (int i = 0; i < 8; i++) {
		BoundingBox newBoundingBox = {
			.min = {
				newPosition.x - dimensions.width / 2,
				newPosition.y - dimensions.height / 2,
				newPosition.z - dimensions.depth / 2
			},
			.max = {
				newPosition.x + dimensions.width / 2,
				newPosition.y + dimensions.height / 2,
				newPosition.z + dimensions.depth / 2
			}
		};

		Vector3 tempPosition = newPosition;

		if (i & 1) {
			newBoundingBox.min.x = currentPosition.x - dimensions.width / 2;
			newBoundingBox.max.x = currentPosition.x + dimensions.width / 2;
			tempPosition.x = currentPosition.x;
		}
		if (i & 2) {
			newBoundingBox.min.z = currentPosition.z - dimensions.depth / 2;
			newBoundingBox.max.z = currentPosition.z + dimensions.depth / 2;
			tempPosition.z = currentPosition.z;
		}
		if (i & 4) {
			newBoundingBox.min.y = currentPosition.y - dimensions.height / 2;
			newBoundingBox.max.y = currentPosition.y + dimensions.height / 2;
			tempPosition.y = currentPosition.y;
		}

		if (!CollisionCheck(newBoundingBox, player, registry)) {
			if (tempPosition.y == currentPosition.y) {
				IsGrounded *isGrounded = registry.try_get<IsGrounded>(player);
				if (isGrounded)
					isGrounded->isGrounded = true;
				movement.velocity.y = 0;
			}
			newPosition = tempPosition;
			boundingBoxComponent.boundingBox = newBoundingBox;
			break;
		}
	}

	camera.position = newPosition;
}

void	PlayerSystem(entt::registry &registry, const float &deltaTime) {
	auto view = registry.view<
		PlayerTag,
		Movement,
		Direction,
		Dimensions,
		CameraComponent,
		BoundingBoxComponent,
		MouseInput
	>();

	for (auto player : view) {

		HandlePlayerKeyboardInput(registry, player);
		UpdatePlayerPosition(registry, player, deltaTime);

		HandlePlayerMouseDirectionInput(registry, player);
		HandlePlayerMouseClickingInput(registry, player);
	}
}

