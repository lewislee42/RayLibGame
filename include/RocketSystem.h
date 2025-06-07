

#ifndef ROCKET_SYSTEM_H 
# define ROCKET_SYSTEM_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

# include <Collision.h>
# include <AssetsManager.h>

void	RocketSystem(entt::registry &registry, const float &deltaTime);
void	SpawnRocket(entt::registry &registry, const entt::entity &shooter, AssetsManager &assetsManager);

#endif /* ROCKET_SYSTEM_H */
