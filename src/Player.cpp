

#include <Player.h>
#include <ObjectsManager.h>
#include <AssetsManager.h>

Player::Player() {

	/* ---- Setting up camera ---- */
	this->camera			= Camera3D();
	this->camera.position	= Vector3{0.0f, 5.1f, 0.0f};
	this->camera.target		= Vector3{0.0f, 0.0f, 1.0f};
	this->camera.up			= Vector3{0.0f, 1.0f, 0.0f};
	this->camera.fovy		= 60.0f;
	this->camera.projection	= CAMERA_PERSPECTIVE;

	/* ---- Setting up Bounding Box ---- */
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

	/* ---- Setting up misc ---- */
	this->_mouseSensitivity = 0.4f;
	this->_playerSpeed = 9.0f;
	this->_velocity = Vector3{0.0f, -1.0f, 0.0f};
	this->_isGrounded = false;
	this->_gravity = -15;
	
}


Player::~Player() {	
}


Vector3	Player::_calculateNewPosition(const float &deltaTime, const Vector3 &currentDirection) {
	Vector3 forward = currentDirection;
	forward.y = 0;
	if (Vector3LengthSqr(forward) > 0.001) {
		forward = Vector3Normalize(forward);
	}
	else {
		forward = Vector3{0.0f, 0.0f, 1.0f};
	}

	_velocity.x = 0;
	_velocity.z = 0;

	Vector3 right = Vector3CrossProduct(forward, camera.up);
	right = Vector3Normalize(right);

	/* ---- Handle WASD ---- */
	if (IsKeyDown(KEY_W)) {
		_velocity = Vector3Add(_velocity, Vector3Scale(forward, _playerSpeed));
	}
	if (IsKeyDown(KEY_S)) {
		_velocity = Vector3Subtract(_velocity, Vector3Scale(forward, _playerSpeed));
	}
	if (IsKeyDown(KEY_D)) {
		_velocity = Vector3Add(_velocity, Vector3Scale(right, _playerSpeed));
	}
	if (IsKeyDown(KEY_A)) {
		_velocity = Vector3Subtract(_velocity, Vector3Scale(right, _playerSpeed));
	}

	/* ---- Handle jumping ---- */
	if (IsKeyDown(KEY_SPACE) && _isGrounded) {
		_velocity.y += 5;
		_isGrounded = false;
	}

	/* ---- Apply gravity ---- */
	if (!_isGrounded) {
		_velocity.y += _gravity * deltaTime;
	}

	return Vector3Add(camera.position, Vector3Scale(_velocity, deltaTime));
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

void	Player::_updatePosition(const Vector3 &newPosition, const ObjectsManager &objectsManager) {
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
			newBoundingBox.min.z = camera.position.z - _playerDepth / 2;
			newBoundingBox.max.z = camera.position.z + _playerDepth / 2;
			tempPosition.z = camera.position.z;
		}
		if (i & 4) {
			newBoundingBox.min.y = camera.position.y - _playerHeight / 2;
			newBoundingBox.max.y = camera.position.y + _playerHeight / 2;
			tempPosition.y = camera.position.y;
		}

		if (!objectsManager.collisionCheck(newBoundingBox)) {
			if (tempPosition.y == camera.position.y) {
				_isGrounded = true;
				_velocity.y = 0;
			}
			camera.position = tempPosition;
			boundingBox = newBoundingBox;
			break;
		}
	}
}

void	Player::_handleShooting(ObjectsManager &objectsManager, AssetsManager &assetsManager) {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector3 direction = Vector3Subtract(camera.target, camera.position);

		Entity* entity = new Entity(
			assetsManager.models["BULLET"],
			Vector3{camera.position.x, camera.position.y, camera.position.z},
			BLACK,
			Vector3Scale(direction, 5.0f),
			Vector3Normalize(direction),
			5,
			true
		);
		objectsManager.entities.push_back(entity);
	}
}

/*
*	This function handles general player input 
*/
void	Player::updatePlayer(const float &deltaTime, ObjectsManager &objectsManager, AssetsManager &assetsManager) {
	Vector3 currentLookDirection = Vector3Subtract(camera.target, camera.position);

	Vector3 newPosition = _calculateNewPosition(deltaTime, currentLookDirection);

	/* ---- Checks & update position ---- */
	_updatePosition(newPosition, objectsManager);

	/* ---- Update direction ---- */
	_updateDirection(currentLookDirection);

	_handleShooting(objectsManager, assetsManager);
}

Vector3	Player::getVelocity() const {
	return _velocity;
}
