

# include <Render3D.h>


void	RenderObjects(entt::registry &registry) {
	auto view = registry.view<ObjectTag, ModelComponent, Position, ColorComponent>();
	for (auto& entity: view) {
		Model &model = registry.get<ModelComponent>(entity).model;
		Vector3 &position = registry.get<Position>(entity).position;
		Color &color = registry.get<ColorComponent>(entity).color;

		DrawModel(model, position, 1, color);
	}
}
