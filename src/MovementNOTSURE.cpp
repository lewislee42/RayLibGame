

# include <Movement.h>
#include <iostream>


void	ApplyGravity(entt::registry &registry, const float &deltaTime) {
	auto view = registry.view<Velocity, Gravity>();
	for (auto entity : view) {
		Vector3& velocity		= registry.get<Velocity>(entity).velocity;
		float& gravity			= registry.get<Gravity>(entity).gravity;

		auto *isGrounded		= registry.try_get<IsGrounded>(entity);
		if (isGrounded) {
			if (isGrounded->isGrounded == false)
				velocity.y += -gravity * deltaTime;
		}
		else {
			velocity.y += -gravity * deltaTime;
		}
	}
}
