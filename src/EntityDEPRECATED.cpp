

# include <Entity.h>
# include <iostream>


Entity::Entity(
	const Model		&model,
	const Vector3	&position,
	const Color		&color,
	const Vector3	&velocity,
	const Vector3	&direction,
	const float		&lifetime,
	const bool		&removeOnCollision
):	Object(model, position, color, direction),
	velocity(velocity),
	lifetime(lifetime),
	removeOnCollision(removeOnCollision)
{
	
	float pitch = asin(-direction.y);
	float yaw = atan2(direction.x, direction.z);
	Matrix pitchMatrix = MatrixRotateX(pitch);
	Matrix yawMatrix   = MatrixRotateY(yaw);
	// First apply pitch, then yaw
	this->model.transform = MatrixMultiply(pitchMatrix, yawMatrix);
}

Entity::~Entity() {
}

void	Entity::updateBoundingBox() {
	boundingBoxWS = {
		.min = Vector3Add(boundingBoxMS.min, position),
		.max = Vector3Add(boundingBoxMS.max, position)
	};
}
