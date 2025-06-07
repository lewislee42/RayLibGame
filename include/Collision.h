

#ifndef COLLISION_H 
# define COLLISION_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

bool	CollisionCheck(const BoundingBox &currentBoundingBox, const entt::entity &currentEntity, entt::registry &registry);

#endif /* COLLISION_H */

