

#ifndef ENTITY_CLASS_H 
# define ENTITY_CLASS_H 

# include <raylib/raylib.h>
# include <Object.h>

class Entity: public Object {
public:
	Vector3	velocity;
	float	lifetime;
	bool	removeOnCollision;

	Entity(
		const Model		&model,
		const Vector3	&position,
		const Color		&color,
		const Vector3	&velocity,
		const Vector3	&direction,
		const float		&lifetime,				// in seconds
		const bool		&removeOnCollision
	);

	~Entity();

	void	updateBoundingBox();
};

#endif /* ENTITY_CLASS_H */
