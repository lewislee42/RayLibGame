

#ifndef WEAPON_SYSTEM_H 
# define WEAPON_SYSTEM_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

# include <Collision.h>
# include <RocketSystem.h>

void	WeaponSystem(entt::registry &registry, const float &deltaTime);

#endif /* WEAPON_SYSTEM_H */

