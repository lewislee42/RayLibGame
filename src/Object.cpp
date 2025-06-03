
# include <Object.h>


Object::Object(const Model &model, const Vector3 &position, const Color &color, const float &scale):
	model(model), position(position), color(color),
	scale(scale), boundingBox(GetMeshBoundingBox(model.meshes[0])) {
	boundingBox = {
		.min = Vector3Add(boundingBox.min, position),
		.max = Vector3Add(boundingBox.max, position)
	};
}

Object::~Object() {
	UnloadModel(model);
}
