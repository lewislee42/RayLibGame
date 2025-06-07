
#ifndef COMPONENTS_H 
# define COMPONENTS_H 

# include <raylib/raylib.h>
# include <entt/entt.hpp>

enum WeaponEnum {
	ROCKET_LAUNCHER = 0
};

struct Position {
	Vector3 position;
};

struct Velocity {
	Vector3 velocity;
};

struct Direction {
	Vector3 direction;
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
};

struct BoundingBoxComponent {
	BoundingBox boundingBox;
};

struct Speed {
	float speed;
};

struct Dimensions {
	float width;
	float height;
	float depth;
};

struct MouseInput {
	float mouseSensitivity;
};

struct IsGrounded {
	bool	isGrounded;
};

struct Gravity {
	float	gravity;
};

struct ModelComponent {
	Model	model;
};

struct ColorComponent {
	Color	color;
};

struct Lifetime {
	float	lifetime;
};

struct WeaponComponent {
	WeaponEnum weaponType;
};

struct EquippedWeapon {
    entt::entity weaponEntity;
};

struct PlayerTag {};
struct ObjectTag {};
struct RocketTag {};

#endif /* COMPONENTS_H */

