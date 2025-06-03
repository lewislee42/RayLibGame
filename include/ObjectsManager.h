

#ifndef OBJECTS_MANAGER_CLASS_H 
# define OBJECTS_MANAGER_CLASS_H 

# include <raylib.h>
# include <vector>
# include <Object.h>

/* this should handle */
class ObjectsManager {
public:
	std::vector <Object *>objects;
	std::vector <Object *>entities;

	~ObjectsManager();

	void	renderObjects() const;	
	void	renderEntities() const;	
	bool	collisionCheck(const BoundingBox &boundingBox) const;
};

#endif /* OBJECTS_MANAGER_CLASS_H */
