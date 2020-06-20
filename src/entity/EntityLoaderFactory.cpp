#include "entity/EntityLoaderFactory.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/SizeComp.hpp"
#include "component/SpriteComp.hpp"

void EntityLoaderFactory::LoadFiles(entt::registry& reg, std::istringstream& reader)
{
	std::cout << "Not implemented. should load files onto screen given certain parameters." << std::endl;
}

void EntityLoaderFactory::LoadBackground(entt::registry& reg, std::istringstream& reader)
{
	auto entity = reg.create();
	auto& size = reg.emplace<SizeComp>(entity);
	size.size.width = ApplicationParameters::k_screenWidth;
	size.size.height = ApplicationParameters::k_screenHeight;
	auto& position = reg.emplace<PositionComp>(entity);
	position.position.x = 0;
	position.position.y = 0;
	auto& spritePath = reg.emplace<SpriteComp>(entity);
	std::string token;
	reader >> token;
	spritePath.filePath = ApplicationParameters::k_spritePath + token + ".png";
}
