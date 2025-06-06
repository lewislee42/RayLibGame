
#ifndef GAME_CLASS_H 
# define GAME_CLASS_H 

# include <Components.h>
# include <entt/entt.hpp>

class Game {
public:
	entt::registry registry;

	Game();

	~Game();
};

#endif /* GAME_CLASS_H */

