


#ifndef ASSETS_MANAGER_CLASS_H 
# define ASSETS_MANAGER_CLASS_H 

# include <raylib.h>
# include <map>
# include <string>

class AssetsManager {
public:
	std::map	<std::string, Model>models;

	AssetsManager();

	~AssetsManager();
};

#endif /* ASSETS_MANAGER_CLASS_H */
