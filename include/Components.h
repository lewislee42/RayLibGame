

#ifndef COMPONENTS_H 
# define COMPONENTS_H 

# include <raylib/raylib.h>
# include <entt/entt.hpp>

enum WeaponEnum {
	ROCKET_LAUNCHER = 0
};

struct PositionAndDirection {
	Vector3 position	= {0};
	Vector3 direction	= {0.0f, 0.0f, 1.0f};
};

struct Movement {
	Vector3 velocity	= {0};
	float	speed		= {0};
};

struct CameraComponent {
	Camera3D	camera = {0};

	CameraComponent() {
		camera.up			= Vector3{0.0f, 1.0f, 0.0f};
		camera.fovy			= 60.0f;
		camera.projection	= CAMERA_PERSPECTIVE;
	};
};

struct Dimensions {
	BoundingBox	boundingBox	= {0};
	float	width			= {1.0f};
	float	height			= {1.0f};
	float	depth			= {1.0f};
};

struct MouseInput {
	float	mouseSensitivity = {0.4};
};

struct GravityComponent {
	bool	isGrounded	= {false};
	float	gravity		= {9.3f};
};

struct ModelComponent {
	Model	model = {0};
	float	scale = {1.0f};
};

struct ColorComponent {
	Color	color = {0};
};


struct Lifetime {
	float	lifetime = {0};
};

struct WeaponComponent {
	WeaponEnum	weaponType;
	float		firerate			= {0};
	float		firerateCooldown	= {0};
	int			ammo				= {0}; // not used yet
};

struct OwnedBy {
	entt::entity	owner;
};

struct EquippedWeapon {
    entt::entity	weaponEntity;
};

struct PlayerTag	{};
struct ObjectTag	{};
struct RocketTag	{};
struct FiringTag	{};

#endif /* COMPONENTS_H */

