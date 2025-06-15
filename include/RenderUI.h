

#ifndef RENDERUI_H 
# define RENDERUI_H 

# include <raylib/raylib.h>
# include <raylib/raymath.h>
# include <entt/entt.hpp>
# include <Components.h>

void	DrawVector(std::string text, const Vector3 &vec, const uint &x, const uint &y);
void	DrawUI(entt::registry &registry);


#endif /* RENDERUI_H */

