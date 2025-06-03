#ifndef PLAYER_CLASS_H
# define PLAYER_CLASS_H

# include <raylib.h>
# include <raymath.h>

class Player {
public:
	Camera3D	camera;

	Player();
	~Player();

	void	updatePlayer(const float &deltaTime);

private:
	float		_playerSpeed;
	float		_mouseSensitivity;

	void	_updateDirection(const Vector3 &currentDirection);
	void	_updatePosition(const float &deltaTime, const Vector3 &currentDirection);
};

#endif /* PLAYER_CLASS_H */
