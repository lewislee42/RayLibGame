
#include <ObjectsManager.h>

ObjectsManager::~ObjectsManager() {
	for (uint i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
}

void	ObjectsManager::renderObjects() const {
	for (uint i = 0; i < objects.size(); i++) {
		DrawModel(objects[i]->model, objects[i]->position, objects[i]->scale, objects[i]->color);
	}
}

void	ObjectsManager::renderEntities() const {
	for (uint i = 0; i < entities.size(); i++) {
		DrawModel(entities[i]->model, entities[i]->position, entities[i]->scale, entities[i]->color);
	}
}

bool	ObjectsManager::collisionCheck(const BoundingBox &boundingBox) const {
	for (uint i = 0; i < objects.size(); i++) {
		if (CheckCollisionBoxes(boundingBox, objects[i]->boundingBox))
			return true;
	}
	return false;
}
