

#ifndef PLAYER_INPUT_H 
# define PLAYER_INPUT_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

void	HandlePlayerKeyboardInput(entt::registry &registry);
void	HandlePlayerMouseInput(entt::registry &registry);

#endif /* PLAYER_INPUT_H */

