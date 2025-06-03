

#include <Player.h>
#include <ObjectsManager.h>

Player::Player() {

	/* ----- Setting up camera ----- */
	this->camera			= Camera3D();
	this->camera.position	= Vector3{0.0f, 1.1f, 0.0f};
	this->camera.target		= Vector3{0.0f, 0.0f, 1.0f};
	this->camera.up			= Vector3{0.0f, 1.0f, 0.0f};
	this->camera.fovy		= 60.0f;
	this->camera.projection	= CAMERA_PERSPECTIVE;

	/* ----- Setting up misc ----- */
	this->_mouseSensitivity = 0.4f;
	this->_playerSpeed = 9.0f;

	this->_playerWidth	= 1;
	this->_playerHeight = 1;
	this->_playerDepth	= 1;

	this->boundingBox = {
		.min = {
			camera.position.x - _playerWidth / 2,
			camera.position.y - _playerHeight / 2,
			camera.position.z - _playerDepth / 2
		},
		.max = {
			camera.position.x + _playerWidth / 2,
			camera.position.y + _playerHeight / 2,
			camera.position.z + _playerDepth / 2
		}
	};

}

Player::~Player() {	
}

Vector3	Player::_calculateNewPosition(const float &deltaTime, const Vector3 &currentDirection) {
	Vector3 newPosition = camera.position;
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
		newPosition = Vector3Add(newPosition, Vector3Scale(forward, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_S)) {
		newPosition = Vector3Subtract(newPosition, Vector3Scale(forward, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_D)) {
		newPosition = Vector3Add(newPosition, Vector3Scale(right, _playerSpeed * deltaTime));
	}
	if (IsKeyDown(KEY_A)) {
		newPosition = Vector3Subtract(newPosition, Vector3Scale(right, _playerSpeed * deltaTime));
	}

	if (IsKeyDown(KEY_SPACE)) {
		newPosition.y += _playerSpeed * deltaTime;
	}
	if (IsKeyDown(KEY_LEFT_CONTROL)) {
		newPosition.y -= _playerSpeed * deltaTime;
	}
	return newPosition;
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
void	Player::updatePlayer(const float &deltaTime, const ObjectsManager &objectsManager) {
	Vector3 currentLookDirection = Vector3Subtract(camera.target, camera.position);

	Vector3 newPosition = _calculateNewPosition(deltaTime, currentLookDirection);

	/* ---- COLLISION CHECKER ---- */
	for (int i = 0; i < 8; i++) {
		BoundingBox newBoundingBox = {
			.min = {
				newPosition.x - _playerWidth / 2,
				newPosition.y - _playerHeight / 2,
				newPosition.z - _playerDepth / 2
			},
			.max = {
				newPosition.x + _playerWidth / 2,
				newPosition.y + _playerHeight / 2,
				newPosition.z + _playerDepth / 2
			}
		};
		Vector3 tempPosition = newPosition;
		if (i & 1) {
			newBoundingBox.min.x = camera.position.x - _playerWidth / 2;
			newBoundingBox.max.x = camera.position.x + _playerWidth / 2;
			tempPosition.x = camera.position.x;
		}
		if (i & 2) {
			newBoundingBox.min.y = camera.position.y - _playerHeight / 2;
			newBoundingBox.max.y = camera.position.y + _playerHeight / 2;
			tempPosition.y = camera.position.y;
		}
		if (i & 4) {
			newBoundingBox.min.z = camera.position.z - _playerDepth / 2;
			newBoundingBox.max.z = camera.position.z + _playerDepth / 2;
			tempPosition.z = camera.position.z;
		}


		if (!objectsManager.collisionCheck(newBoundingBox)) {
			camera.position = tempPosition;
			boundingBox = newBoundingBox;
			break;
		}
	}


	this->_updateDirection(currentLookDirection);

}
