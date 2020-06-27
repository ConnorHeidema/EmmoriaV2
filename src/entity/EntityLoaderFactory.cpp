#include "entity/EntityLoaderFactory.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/EntityLoaderUtils.hpp"

#include "component/tag/ButtonComp.hpp"
#include "component/tag/DialogChainComp.hpp"
#include "component/tag/RandomComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/SpriteComp.hpp"

#include <SFML/Graphics.hpp>

#include <string>

void EntityLoaderFactory::LoadFile(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();

	rReg.emplace<ButtonComp>(entity);

	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
	renderableComp.m_bRendered = false;

	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	auto& positionComp = rReg.emplace<PositionComp>(entity);
	rReg.emplace<ClickableComp>(entity);

	std::string token;
	reader >> token;
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

	auto& textComp = rReg.emplace<TextComp>(entity);
	textComp.m_text = ReadString_(reader);

	sizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(textComp.m_text, sizeComp.m_size.height);

}

void EntityLoaderFactory::LoadBackground(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();
	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
	renderableComp.m_bRendered = false;

	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	sizeComp.m_size.width = ApplicationParameters::k_screenWidth;
	sizeComp.m_size.height = ApplicationParameters::k_screenHeight;

	auto& positionComp = rReg.emplace<PositionComp>(entity);
	positionComp.m_position.x = 50 * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	positionComp.m_position.y = 50 * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

	auto& spriteComp = rReg.emplace<SpriteComp>(entity);
	std::string token;
	reader >> token;
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
}

void EntityLoaderFactory::LoadRandomDialog(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();
	rReg.emplace<DialogChainComp>(entity);
	rReg.emplace<RandomComp>(entity);

	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	auto& textComp = rReg.emplace<TextComp>(entity);

	std::string token;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	sizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(textComp.m_text, sizeComp.m_size.height);
	textComp.m_text = ReadString_(reader);
}

std::string EntityLoaderFactory::ReadString_(std::istringstream& reader)
{
	std::string stringToRead;
	std::string token;
	while (reader >> token) { stringToRead += token + " "; }
	stringToRead.pop_back();
	return stringToRead;
}