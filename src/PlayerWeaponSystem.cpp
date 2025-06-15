

#include <PlayerWeaponSystem.h>


# include <iostream>
void	PlayerWeaponSystem(entt::registry &registry, const float &deltaTime, AssetsManager &assetsManager) {
	auto view = registry.view<WeaponComponent, OwnedBy>();
	for (auto &entity : view) {
		WeaponEnum &weaponType	= registry.get<WeaponComponent>(entity).weaponType;
		float &firerate			= registry.get<WeaponComponent>(entity).firerate;
		float &firerateCooldown	= registry.get<WeaponComponent>(entity).firerateCooldown;

		entt::entity ownedBy	= registry.get<OwnedBy>(entity).owner;
		if (!registry.valid(ownedBy)) {
			continue;
		}

		if (firerateCooldown >= 0)
			firerateCooldown -= deltaTime;

		if (firerateCooldown <= 0 && registry.all_of<FiringTag>(ownedBy)) {
			switch (weaponType) {
				case ROCKET_LAUNCHER:
					SpawnRocket(registry, ownedBy, assetsManager);
					break;
			}
			firerateCooldown = firerate;
		}
	}
}
