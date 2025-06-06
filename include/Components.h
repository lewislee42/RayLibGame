
#ifndef COMPONENTS_H 
# define COMPONENTS_H 

# include <raylib/raylib.h>

struct Position {
	Vector3 position;

	operator Vector3 &() { return position; }
};

struct Velocity {
	Vector3 velocity;

	operator Vector3 &() { return velocity; }
};

struct Direction {
	Vector3 direction;

	operator Vector3 &() { return direction; }
};

struct CameraComponent {
	Camera3D	camera;

	CameraComponent() {
		camera				= Camera3D();
		camera.position		= Vector3{0.0f, 5.1f, 0.0f};
		camera.target		= Vector3{0.0f, 5.1f, 1.0f};
		camera.up			= Vector3{0.0f, 1.0f, 0.0f};
		camera.fovy			= 60.0f;
		camera.projection	= CAMERA_PERSPECTIVE;
	};
	CameraComponent(const Vector3 &position) {
		camera				= Camera3D();
		camera.position		= position;
		camera.target		= Vector3{0.0f, 0.0f, 1.0f};
		camera.up			= Vector3{0.0f, 1.0f, 0.0f};
		camera.fovy			= 60.0f;
		camera.projection	= CAMERA_PERSPECTIVE;
	};

	operator Camera3D &() { return camera; }
};

struct CollisionBox {
	BoundingBox boundingBox;

	operator BoundingBox &() { return boundingBox; }
};

struct Speed {
	float speed;
	
	operator float &() { return speed; }
};

struct Size {
	float width;
	float height;
	float depth;
};

struct MouseInput {
	float mouseSensitivity;

	operator float &() { return mouseSensitivity; }
};

struct IsGrounded {
	bool	isGrounded;

	operator bool &() { return isGrounded; }
};

struct Gravity {
	float	gravity;

	operator float &() { return gravity; }
};

struct KeyboardInputTag {};


struct PlayerTag {};
/*struct BulletTag {};   // Empty tag*/
/*struct EnemyTag {};    // Another tag*/

#endif /* COMPONENTS_H */

