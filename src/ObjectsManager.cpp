
#include "raylib.h"
#include <ObjectsManager.h>

#include <iostream>
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
		if (CheckCollisionBoxes(boundingBox, objects[i]->boundingBoxWS))
			return true;
	}
	return false;
}

void	ObjectsManager::updateEntities(float deltaTime) {
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i]->lifetime - deltaTime <= 0) {
			entities.erase(entities.begin() + i); // removing it for now
			continue;
		}
		entities[i]->position = Vector3Add(entities[i]->position, Vector3Scale(entities[i]->velocity, deltaTime));
		entities[i]->lifetime -= deltaTime;
		entities[i]->updateBoundingBox();
	}
}
