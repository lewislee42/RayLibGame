

#include <Player.h>

Player::Player() {

	/* ----- Setting up camera ----- */
	this->camera			= Camera3D();
	this->camera.position	= Vector3{0.0f, 0.3f, 0.0f};
	this->camera.target		= Vector3{0.0f, 0.0f, 1.0f};
	this->camera.up			= Vector3{0.0f, 1.0f, 0.0f};
	this->camera.fovy		= 60.0f;
	this->camera.projection	= CAMERA_PERSPECTIVE;

	/* ----- Setting up misc ----- */
	this->_mouseSensitivity = 0.4f;
	this->_playerSpeed = 9.0f;

}

Player::~Player() {	
}

void	Player::_updatePosition(const float &deltaTime, const Vector3 &currentDirection) {
	Vector3 forward = currentDirection;
	forward.y = 0;
	if (Vector3LengthSqr(forward) > 0.001) {
		forward = Vector3Normalize(forward);
	}
	else {
		forward = Vector3{0.0f, 0.0f, 1.0f};
	}

	Vector3 right = Vector3CrossProduct(forward, camera.up);
	right = Vector3Normalize(right);

	if (IsKeyDown(KEY_W)) {
		camera.position = Vector3Add(camera.position, Vector3Scale(forward, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_S)) {
		camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_D)) {
		camera.position = Vector3Add(camera.position, Vector3Scale(right, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_A)) {
		camera.position = Vector3Subtract(camera.position, Vector3Scale(right, _playerSpeed * deltaTime));
	}

	if (IsKeyDown(KEY_SPACE)) {
		camera.position.y += _playerSpeed * deltaTime;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL)) {
		camera.position.y -= _playerSpeed * deltaTime;
	}
}

void	Player::_updateDirection(const Vector3 &currentDirection) {
	Vector2 mouseDelta = GetMouseDelta();
    Vector3 currentLookDirection = Vector3Normalize(currentDirection);

	Vector3 yawAxis = { 0.0f, 1.0f, 0.0f };
    float yawAngle = -mouseDelta.x * _mouseSensitivity;
    currentLookDirection = Vector3RotateByAxisAngle(currentLookDirection, yawAxis, yawAngle * DEG2RAD);

	Vector3 localRight = Vector3CrossProduct(currentLookDirection, camera.up);
    localRight = Vector3Normalize(localRight);
    float pitchAngle = -mouseDelta.y * _mouseSensitivity;
	currentLookDirection = Vector3RotateByAxisAngle(currentLookDirection, localRight, pitchAngle * DEG2RAD);

	currentLookDirection = Vector3Normalize(currentLookDirection);
	camera.target = Vector3Add(camera.position, currentLookDirection);
}

/*
*	This function handles Player movement and direction 
*/
void	Player::updatePlayer(const float &deltaTime) {
	Vector3 currentLookDirection = Vector3Subtract(camera.target, camera.position);

	// need to update this to calculate the new position only
	this->_updatePosition(deltaTime, currentLookDirection);

	this->_updateDirection(currentLookDirection);

}
