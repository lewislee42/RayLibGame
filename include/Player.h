#ifndef PLAYER_CLASS_H
# define PLAYER_CLASS_H

# include <raylib.h>
# include <raymath.h>

class ObjectsManager;

class Player {
public:
	Camera3D	camera;
	BoundingBox	boundingBox;

	Player();
	~Player();

	void	updatePlayer(const float &deltaTime, const ObjectsManager& objectsManager);
	Vector3	getVelocity() const;

private:
	float	_playerSpeed;
	float	_mouseSensitivity;
	float	_gravity;
	Vector3	_velocity;
	bool	_isGrounded;

	float	_playerWidth;
	float	_playerHeight;
	float	_playerDepth;

	void	_updateDirection(const Vector3 &currentDirection);
	Vector3	_calculateNewPosition(const float &deltaTime, const Vector3 &currentDirection);
};

#endif /* PLAYER_CLASS_H */
