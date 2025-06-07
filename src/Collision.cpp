

# include <Collision.h>


bool	CollisionCheck(const BoundingBox &currentBoundingBox, const entt::entity &currentEntity, entt::registry &registry) {
	auto view = registry.view<BoundingBoxComponent>();
	for (auto &entity : view) {
		if (entity == currentEntity)
			continue;

		BoundingBox &boundingBox = registry.get<BoundingBoxComponent>(entity).boundingBox;
		if (CheckCollisionBoxes(currentBoundingBox, boundingBox))
			return true;
	}
	return false;
}

