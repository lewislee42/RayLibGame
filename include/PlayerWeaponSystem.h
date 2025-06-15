

#ifndef PLAYER_WEAPON_SYSTEM_H 
# define PLAYER_WEAPON_SYSTEM_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

# include <RocketSystem.h>
# include <AssetsManager.h>

void	PlayerWeaponSystem(entt::registry &registry, const float &deltaTime, AssetsManager &assetsManager);

#endif /* PLAYER_WEAPON_SYSTEM_H */

