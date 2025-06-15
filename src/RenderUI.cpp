

# include <RenderUI.h>


void	DrawVector(std::string text, const Vector3 &vec, const uint &x, const uint &y) {
	text += ": x " + std::to_string(vec.x);
	text += ", y " + std::to_string(vec.y);
	text += ", z " + std::to_string(vec.z);
	DrawText(text.c_str(), x, y, 10, BLACK);
}

void	DrawUI(entt::registry &registry) {
	auto view = registry.view<PlayerTag>();

	entt::entity player 			= *view.begin();
	PositionAndDirection& posDir	= registry.get<PositionAndDirection>(player);
	Movement& movement				= registry.get<Movement>(player);

	auto rocketsView = registry.view<RocketTag>();
	int rocketCount = rocketsView.size();

	DrawFPS(10, 10);
	DrawVector("position", posDir.position, 10, 40);
	DrawVector("direction", posDir.direction, 10, 50);
	DrawVector("velocity", movement.velocity, 10, 60);
	std::string rocketString("Rockets in scene: " + std::to_string(rocketCount));
	DrawText(rocketString.c_str(), 10, 70, 10, BLACK);
}
