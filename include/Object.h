
#ifndef OBJECT_CLASS_H
# define OBJECT_CLASS_H

# include <raylib/raylib.h>
# include <raylib/raymath.h>

class Object {
public:
	Model		model;
	Vector3		position;
	Color		color;
	Vector3		direction;
	BoundingBox	boundingBoxMS;	// model space
	BoundingBox	boundingBoxWS;	// world space

	Object(
		const Model		&model,
		const Vector3	&position,
		const Color		&color,
		const Vector3	&direction
	);
	~Object();
};

#endif /* OBJECT_CLASS_H */
