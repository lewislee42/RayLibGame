

#ifndef PLAYER_SYSTEM_H 
# define PLAYER_SYSTEM_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

# include <Collision.h>
# include <RocketSystem.h>
# include <AssetsManager.h>

void	HandlePlayerKeyboardInput(entt::registry &registry, const entt::entity &player);
void	HandlePlayerMouseDirectionInput(entt::registry &registry, const entt::entity &player);
void	HandlePlayerMouseClickingInput(entt::registry &registry, const entt::entity &player, AssetsManager &assetsManager);
void	UpdatePlayerPosition(entt::registry &registry, const entt::entity &player, const float &deltaTime);
void	PlayerSystem(entt::registry &registry, const float &deltaTime, AssetsManager &assetsManager);

#endif /* PLAYER_SYSTEM_H */

