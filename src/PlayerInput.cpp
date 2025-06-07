

#include <PlayerInput.h>


void	HandlePlayerKeyboardInput(entt::registry &registry) {
	auto view = registry.view<PlayerTag, Velocity, CameraComponent, Speed, IsGrounded, Direction>();
	for (auto entity : view) {
		Vector3& velocity	= registry.get<Velocity>(entity).velocity;
		Camera3D& camera	= registry.get<CameraComponent>(entity).camera;
		float& speed		= registry.get<Speed>(entity).speed;
		bool& isGrounded	= registry.get<IsGrounded>(entity).isGrounded;
		Vector3& direction	= registry.get<Direction>(entity).direction;
	
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

void	HandlePlayerMouseInput(entt::registry &registry) {
	auto view = registry.view<PlayerTag, MouseInput, Velocity, CameraComponent, Direction>();	
	for (auto entity : view) {
		Camera3D& camera		= registry.get<CameraComponent>(entity).camera;
		float& mouseSensitivity	= registry.get<MouseInput>(entity).mouseSensitivity;
		Vector3& direction		= registry.get<Direction>(entity).direction;

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
