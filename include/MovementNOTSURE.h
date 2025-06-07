

#ifndef MOVEMENT_H 
# define MOVEMENT_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>
# include <Collision.h>

void	ApplyGravity(entt::registry &registry, const float &deltaTime);

#endif /* MOVEMENT_H */

