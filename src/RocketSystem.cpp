

#include <RocketSystem.h>


#include <iostream>
void	RocketSystem(entt::registry &registry, const float &deltaTime, AssetsManager &assetsManager) {
	auto view = registry.view<RocketTag, Movement, Position, Dimensions, BoundingBoxComponent, Lifetime>();

	for (auto &entity : view) {
		Vector3 &position			= registry.get<Position>(entity).position;
		Movement &movement			= registry.get<Movement>(entity);
		Dimensions dimensions		= registry.get<Dimensions>(entity);
		BoundingBox	&boundingBox	= registry.get<BoundingBoxComponent>(entity).boundingBox;
		float &lifetime 			= registry.get<Lifetime>(entity).lifetime;

		lifetime -= deltaTime;
		if (lifetime <= 0) {
			registry.destroy(entity); // delete as of now
			continue;
		}


		Vector3 newPosition = Vector3Add(position, Vector3Scale(movement.velocity, movement.speed * deltaTime));
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

		
		if (CollisionCheck(newBoundingBox, entity, registry)) {
			registry.destroy(entity); // delete as of now
			// spawn explosion
			continue ;
		}
		position = newPosition;
		boundingBox = newBoundingBox;
	}
}


void	SpawnRocket(entt::registry &registry, const entt::entity &shooter, AssetsManager &assetsManager) {
	entt::entity rocket = registry.create();

	Vector3 &direction = registry.get<Direction>(shooter).direction;
	Vector3 position;
	Position *pos = registry.try_get<Position>(shooter);
	CameraComponent *camera = registry.try_get<CameraComponent>(shooter);
	if (pos)
		position = pos->position;
	else if (camera) 
		position = camera->camera.position;

	Model &model = assetsManager.models["ROCKET"];
	Vector3 newPosition = Vector3Add(position, direction);
	float speed = 10.0f;
	registry.emplace<RocketTag>(rocket);
	registry.emplace<ModelComponent>(rocket, model, 1.0f);
	registry.emplace<Position>(rocket, newPosition);
	registry.emplace<Direction>(rocket, direction);
	registry.emplace<ColorComponent>(rocket, BLACK);
	registry.emplace<Movement>(rocket, Vector3Scale(direction, speed), speed);
	registry.emplace<Lifetime>(rocket, 5.0f);
	/*registry.emplace<Damage>(rocket, 60.0f);	// not used yet*/
	BoundingBox boundingBox = GetMeshBoundingBox(model.meshes[0]);
	for (int i = 1; i < model.meshCount; i++) {
		BoundingBox meshBoundingBox = GetMeshBoundingBox(model.meshes[i]);

		boundingBox.min.x = fminf(boundingBox.min.x, meshBoundingBox.min.x);
		boundingBox.min.y = fminf(boundingBox.min.y, meshBoundingBox.min.y);
		boundingBox.min.z = fminf(boundingBox.min.z, meshBoundingBox.min.z);


		boundingBox.max.x = fminf(boundingBox.max.x, meshBoundingBox.max.x);
		boundingBox.max.y = fminf(boundingBox.max.y, meshBoundingBox.max.y);
		boundingBox.max.z = fminf(boundingBox.max.z, meshBoundingBox.max.z);
	}
	registry.emplace<Dimensions>(
		rocket,
		boundingBox.max.x - boundingBox.min.x,
		boundingBox.max.y - boundingBox.min.y, 
		boundingBox.max.z - boundingBox.min.z
	);
	boundingBox = {
		.min = Vector3Add(boundingBox.min, newPosition),
		.max = Vector3Add(boundingBox.max, newPosition)
	};
	registry.emplace<BoundingBoxComponent>(rocket, boundingBox);

	Model &uploadedModel = registry.get<ModelComponent>(rocket).model;
	float pitch = asin(-direction.y);
	float yaw = atan2(direction.x, direction.z);
	Matrix pitchMatrix = MatrixRotateX(pitch);
	Matrix yawMatrix   = MatrixRotateY(yaw);
	uploadedModel.transform = MatrixMultiply(pitchMatrix, yawMatrix);
}
