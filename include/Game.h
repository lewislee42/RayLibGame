

#ifndef GAME_CLASS_H 
# define GAME_CLASS_H 

# include <AssetsManager.h>
# include <Components.h>
# include <entt/entt.hpp>

# include <PlayerInput.h>
# include <Movement.h>
# include <Collision.h>
# include <Render3D.h>
# include <RenderUI.h>

class Game {
public:
	entt::registry registry;

	void	Run();

	Game();
	~Game();
private:
	AssetsManager	assetsManager;

	void	InitPlayer();
	void	InitScene();
};

#endif /* GAME_CLASS_H */

