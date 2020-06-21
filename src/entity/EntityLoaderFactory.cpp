#include "entity/EntityLoaderFactory.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/SizeComp.hpp"
#include "component/SpriteComp.hpp"
#include "component/ClickableComp.hpp"
#include "component/RenderableComp.hpp"

#include <string>

void EntityLoaderFactory::LoadFiles(entt::registry& reg, std::istringstream& reader)
{
	auto entity = reg.create();
	auto& size = reg.emplace<SizeComp>(entity);
	auto& position = reg.emplace<PositionComp>(entity);
	reg.emplace<RenderableComp>(entity);
	reg.emplace<ClickableComp>(entity);

	std::string token;
	reader >> token;
	position.position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	position.position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
	reader >> token;
	size.size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;;
	reader >> token;
	size.size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;;
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
