

# include <Entity.h>


Entity::Entity(
	const Model		&model,
	const Vector3	&position,
	const Color		&color,
	const float		&scale,
	const Vector3	&velocity,
	const Vector3	&direction,
	const float		&lifetime
):	Object(model, position, color, scale, direction),
	velocity(velocity),
	lifetime(lifetime)
{
	
	/*float pitch = asin(-direction.y);*/
	/*pitch = 45;*/
	/*float yaw = atan2(direction.x, direction.z);*/
	/*this->model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*pitch, DEG2RAD*yaw, 0 });*/
}

Entity::~Entity() {
}
