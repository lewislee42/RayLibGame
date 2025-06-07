

#include "RocketSystem.h"
#include <WeaponSystem.h>


void	WeaponSystem(entt::registry &registry, const float &deltaTime) {
	// retrieve weapon equipped
	/*auto view = registry.view<WeaponComponent>();*/
	/**/
	/*if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {*/
	/*	for (auto &entity : view) {*/
	/*		WeaponEnum weaponType = registry.get<WeaponComponent>(entity).weaponType;*/
	/*		switch (weaponType) {*/
	/*			case WeaponEnum::ROCKET_LAUNCHER:*/
	/*				SpawnRocket(registry, );*/
	/*		}*/
	/*	}*/
	/*}*/

	RocketSystem(registry, deltaTime);
}
