#include "entity/EntityLoaderFactory.hpp"

#include "component/tag/ButtonComp.hpp"
#include "component/tag/RandomComp.hpp"
#include "component/tag/PlayerComp.hpp"
#include "component/tag/DialogChainComp.hpp"
#include "component/tag/DialogChainFragmentComp.hpp"
#include "component/tag/PersistentComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/EntityLoaderUtils.hpp"

#include <string>
#include <iostream>

#include "entity/EntityMacro.hpp"

#define LOAD_DEF_TAG(name) \
void EntityLoaderFactory::Load##name(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader) \
{ rReg.emplace_or_replace< name >(rEntity); }
ALL_TAG_MACRO(LOAD_DEF_TAG)
#undef LOAD_DEF

void EntityLoaderFactory::LoadFullscreen(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	LoadRenderable(rReg, rEntity, reader);
	LoadSprite(rReg, rEntity, reader);
	std::istringstream shallowReader("50 50 100 100");
	LoadXposition(rReg, rEntity, shallowReader);
	LoadYposition(rReg, rEntity, shallowReader);
	LoadWidth(rReg, rEntity, shallowReader);
	LoadHeight(rReg, rEntity, shallowReader);
}

void EntityLoaderFactory::LoadRenderable(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& renderableComp = rReg.get_or_emplace<RenderableComp>(rEntity);
	renderableComp.m_bRendered = false;
}

void EntityLoaderFactory::LoadXposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
}

void EntityLoaderFactory::LoadYposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
}

void EntityLoaderFactory::LoadHeight(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
}

void EntityLoaderFactory::LoadWidth(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
}

void EntityLoaderFactory::LoadText(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& textComp = rReg.get_or_emplace<TextComp>(rEntity);
	std::string token;
	while (token != "*")
	{
		reader >> token;
		textComp.m_text += token;
	}
}

void EntityLoaderFactory::LoadSprite(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& spriteComp = rReg.get_or_emplace<SpriteComp>(rEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
}

std::string EntityLoaderFactory::ReadString_(std::istringstream& reader)
{
	std::string stringToRead;
	std::string token;
	while (reader >> token) { stringToRead += token + " "; }
	stringToRead.pop_back();
	return stringToRead;
}

#include "entity/EntityMacroEnd.hpp"

// void EntityLoaderFactory::LoadFile(entt::registry& rReg, std::istringstream& reader)
// {
// 	auto entity = rReg.create();

// 	rReg.emplace<ButtonComp>(entity);

// 	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
// 	renderableComp.m_bRendered = false;

// 	auto& sizeComp = rReg.emplace<SizeComp>(entity);
// 	auto& positionComp = rReg.emplace<PositionComp>(entity);
// 	rReg.emplace<ClickableComp>(entity);

// 	std::string token;
// 	reader >> token;
// 	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	reader >> token;
// 	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
// 	reader >> token;
// 	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& textComp = rReg.emplace<TextComp>(entity);
// 	textComp.m_text = ReadString_(reader);

// 	sizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(textComp.m_text, sizeComp.m_size.height);

// }

// void EntityLoaderFactory::LoadBackground(entt::registry& rReg, std::istringstream& reader)
// {
// 	auto entity = rReg.create();
// 	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
// 	renderableComp.m_bRendered = false;

// 	auto& sizeComp = rReg.emplace<SizeComp>(entity);
// 	sizeComp.m_size.width = ApplicationParameters::k_screenWidth;
// 	sizeComp.m_size.height = ApplicationParameters::k_screenHeight;

// 	auto& positionComp = rReg.emplace<PositionComp>(entity);
// 	positionComp.m_position.x = 50 * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	positionComp.m_position.y = 50 * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& spriteComp = rReg.emplace<SpriteComp>(entity);
// 	std::string token;
// 	reader >> token;
// 	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
// }

// void EntityLoaderFactory::LoadRandomDialog(entt::registry& rReg, std::istringstream& reader)
// {
// 	auto entity = rReg.create();
// 	rReg.emplace<DialogChainComp>(entity);
// 	rReg.emplace<RandomComp>(entity);

// 	auto& sizeComp = rReg.emplace<SizeComp>(entity);
// 	auto& textComp = rReg.emplace<TextComp>(entity);

// 	std::string token;
// 	reader >> token;
// 	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	sizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(textComp.m_text, sizeComp.m_size.height);
// 	textComp.m_text = ReadString_(reader);
// }

// void EntityLoaderFactory::LoadPlayer(entt::registry& rReg, std::istringstream& reader)
// {
// 	std::cout << "loading player" << std::endl;
// 	std::string token;

// 	auto entity = rReg.create();
// 	rReg.emplace<PlayerComp>(entity);

// 	auto& positionComp = rReg.emplace<PositionComp>(entity);
// 	reader >> token;
// 	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	reader >> token;
// 	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
// 	renderableComp.m_bRendered = false;

// 	auto& sizeComp = rReg.emplace<SizeComp>(entity);
// 	reader >> token;
// 	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	reader >> token;
// 	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& spriteComp = rReg.emplace<SpriteComp>(entity);
// 	reader >> token;
// 	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";

// 	auto& healthComp = rReg.emplace<HealthComp>(entity);
// 	reader >> token;
// 	healthComp.m_health = std::stoi(token);
// }

// void EntityLoaderFactory::LoadHealingPad(entt::registry& rReg, std::istringstream& reader)
// {
// 	std::cout << "loading healing pad" << std::endl;
// 	std::string token;

// 	auto entity = rReg.create();
// 	auto& interactableComp = rReg.emplace<InteractableComp>(entity);
// 	interactableComp.interactionType = "heal";

// 	auto& positionComp = rReg.emplace<PositionComp>(entity);
// 	reader >> token;
// 	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	reader >> token;
// 	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
// 	renderableComp.m_bRendered = false;

// 	auto& sizeComp = rReg.emplace<SizeComp>(entity);
// 	reader >> token;
// 	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
// 	reader >> token;
// 	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

// 	auto& spriteComp = rReg.emplace<SpriteComp>(entity);
// 	reader >> token;
// 	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
// }