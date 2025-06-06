
# include <Object.h>

#include <cmath>
#include <iostream>

Object::Object(
	const Model		&model,
	const Vector3	&position,
	const Color		&color,
	const Vector3	&direction
):	model(model),
	position(position),
	color(color),
	direction(direction)
{
	boundingBoxMS = GetMeshBoundingBox(model.meshes[0]);

	for (int i = 1; i < model.meshCount; i++) {
		BoundingBox meshBoundingBox = GetMeshBoundingBox(model.meshes[i]);

		boundingBoxMS.min.x = fminf(boundingBoxMS.min.x, meshBoundingBox.min.x);
		boundingBoxMS.min.y = fminf(boundingBoxMS.min.y, meshBoundingBox.min.y);
		boundingBoxMS.min.z = fminf(boundingBoxMS.min.z, meshBoundingBox.min.z);


		boundingBoxMS.max.x = fminf(boundingBoxMS.max.x, meshBoundingBox.max.x);
		boundingBoxMS.max.y = fminf(boundingBoxMS.max.y, meshBoundingBox.max.y);
		boundingBoxMS.max.z = fminf(boundingBoxMS.max.z, meshBoundingBox.max.z);
	}

	boundingBoxWS = {
		.min = Vector3Add(boundingBoxMS.min, position),
		.max = Vector3Add(boundingBoxMS.max, position)
	};
}



Object::~Object() {
}
