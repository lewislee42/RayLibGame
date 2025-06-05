

#ifndef ENTITY_CLASS_H 
# define ENTITY_CLASS_H 

# include <raylib.h>
# include <Object.h>

class Entity: public Object {
public:
	Vector3	velocity;
	float	lifetime;

	Entity(
		const Model		&model,
		const Vector3	&position,
		const Color		&color,
		const float		&scale,
		const Vector3	&velocity,
		const Vector3	&direction,
		const float		&lifetime		// in seconds
	);

	~Entity();

	void	updateBoundingBox();
};

#endif /* ENTITY_CLASS_H */
