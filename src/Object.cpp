
#include "raylib.h"
# include <Object.h>

#include <iostream>
Object::Object(
	const Model		&model,
	const Vector3	&position,
	const Color		&color,
	const float		&scale,
	const Vector3	&direction
):	model(model),
	position(position),
	color(color),
	scale(scale),
	direction(direction),
	boundingBox(GetMeshBoundingBox(model.meshes[0]))
{
	boundingBox = {
		.min = Vector3Add(boundingBox.min, position),
		.max = Vector3Add(boundingBox.max, position)
	};


	std::cout << "direction: x " << direction.x << ", y " << direction.y << ", z " << direction.z << std::endl;
	float pitch = asin(-direction.y);
	float yaw = atan2(direction.x, direction.z);
	std::cout << "pitch: " << (pitch) << ", yaw:" << (yaw ) <<  std::endl;
	this->model.transform = MatrixRotateXYZ((Vector3){ 0, yaw, 0 });
}

Object::~Object() {
	UnloadModel(model);
}
