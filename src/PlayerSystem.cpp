

#include <PlayerSystem.h>


# include <iostream>
void	HandlePlayerKeyboardInput(entt::registry &registry, const entt::entity &player) {
	Vector3& velocity	= registry.get<Velocity>(player).velocity;
	Camera3D& camera	= registry.get<CameraComponent>(player).camera;
	float& speed		= registry.get<Speed>(player).speed;
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

void	HandlePlayerMouseClickingInput(entt::registry &registry, const entt::entity &player, AssetsManager &assetsManager) {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		auto view = registry.view<EquippedWeapon>();
		for (auto &entity : view) {
			entt::entity weaponId = registry.get<EquippedWeapon>(entity).weaponEntity;
			if (!registry.valid(weaponId))
				continue ;

			WeaponEnum &weaponType = registry.get<WeaponComponent>(weaponId).weaponType;

			switch (weaponType) {
				case ROCKET_LAUNCHER:
					SpawnRocket(registry, player, assetsManager);
					break;
			}
		}
	}
}

void	UpdatePlayerPosition(entt::registry &registry, const entt::entity &player, const float &deltaTime) {
	Vector3 newPosition;
	Vector3 currentPosition;
	Vector3& velocity			= registry.get<Velocity>(player).velocity;
	if (velocity.x == 0 && velocity.y == 0 && velocity.z == 0)
		return ;


	Camera3D &camera			= registry.get<CameraComponent>(player).camera;
	currentPosition = camera.position;
	newPosition = Vector3Add(camera.position, Vector3Scale(velocity, deltaTime));

	
	IsGrounded *isGrounded		= registry.try_get<IsGrounded>(player);
	Gravity *gravity			= registry.try_get<Gravity>(player);
	if (isGrounded && gravity) {
		if (isGrounded->isGrounded == false)
			velocity.y += -gravity->gravity * deltaTime;
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
				velocity.y = 0;
			}
			newPosition = tempPosition;
			boundingBoxComponent.boundingBox = newBoundingBox;
			break;
		}
	}

	camera.position = newPosition;
}

void	PlayerSystem(entt::registry &registry, const float &deltaTime, AssetsManager &assetsManager) {
	auto view = registry.view<
		PlayerTag,
		Velocity,
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
		HandlePlayerMouseClickingInput(registry, player, assetsManager);
	}
}

