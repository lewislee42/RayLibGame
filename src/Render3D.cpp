

# include <Render3D.h>


void	RenderObjects(entt::registry &registry) {
	auto view = registry.view<ModelComponent, Position, ColorComponent>();
	for (auto& entity: view) {
		ModelComponent &model	= registry.get<ModelComponent>(entity);
		Vector3 &position		= registry.get<Position>(entity).position;
		Color &color			= registry.get<ColorComponent>(entity).color;

		DrawModel(model.model, position, model.scale, color);
	}
}
