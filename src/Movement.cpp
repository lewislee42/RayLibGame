

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

void	UpdatePosition(entt::registry &registry, const float &deltaTime) {
	auto view = registry.view<Velocity>();
	for (auto entity : view) {
		Vector3 newPosition;
		Vector3 currentPosition;
		Vector3& velocity			= registry.get<Velocity>(entity).velocity;
		if (velocity.x == 0 && velocity.y == 0 && velocity.z == 0)
			continue ;


		Position *position			= registry.try_get<Position>(entity);
		CameraComponent *camera		= registry.try_get<CameraComponent>(entity);
		if (position) {
			currentPosition = position->position;
			newPosition = Vector3Add(position->position, Vector3Scale(velocity, deltaTime));
		}
		else if (camera) {
			currentPosition = camera->camera.position;
			newPosition = Vector3Add(camera->camera.position, Vector3Scale(velocity, deltaTime));
		}


		Dimensions& dimensions						= registry.get<Dimensions>(entity);
		BoundingBoxComponent *boundingBoxComponent	= registry.try_get<BoundingBoxComponent>(entity);
		if (boundingBoxComponent) {
			for (int i = 0; i < 8; i++) {
				BoundingBox newBoundingBox = {
					.min = {
						newPosition.x - dimensions.width / 2,
						newPosition.y - dimensions.height / 2,
						newPosition.z - dimensions.depth / 2
					},
					.max = {
						newPosition.x + dimensions.width / 2,
						newPosition.y + dimensions.height / 2,
						newPosition.z + dimensions.depth / 2
					}
				};

				Vector3 tempPosition = newPosition;

				if (i & 1) {
					newBoundingBox.min.x = currentPosition.x - dimensions.width / 2;
					newBoundingBox.max.x = currentPosition.x + dimensions.width / 2;
					tempPosition.x = currentPosition.x;
				}
				if (i & 2) {
					newBoundingBox.min.z = currentPosition.z - dimensions.depth / 2;
					newBoundingBox.max.z = currentPosition.z + dimensions.depth / 2;
					tempPosition.z = currentPosition.z;
				}
				if (i & 4) {
					newBoundingBox.min.y = currentPosition.y - dimensions.height / 2;
					newBoundingBox.max.y = currentPosition.y + dimensions.height / 2;
					tempPosition.y = currentPosition.y;
				}

				if (!CollisionCheck(newBoundingBox, entity, registry)) {
					if (tempPosition.y == currentPosition.y) {
						IsGrounded *isGrounded = registry.try_get<IsGrounded>(entity);
						if (isGrounded)
							isGrounded->isGrounded = true;
						velocity.y = 0;
					}
					newPosition = tempPosition;
					boundingBoxComponent->boundingBox = newBoundingBox;
					break;
				}
			}

		}

		if (position)
			position->position = newPosition; 
		else if (camera)
			camera->camera.position = newPosition;
	}
}
