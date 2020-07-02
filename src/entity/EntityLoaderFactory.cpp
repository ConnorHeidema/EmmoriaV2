#include "entity/EntityLoaderFactory.hpp"

#include "component/tag/DialogChainComp.hpp"
#include "component/tag/DialogChainFragmentComp.hpp"
#include "component/tag/PersistentComp.hpp"
#include "component/tag/PlayerComp.hpp"
#include "component/tag/RandomComp.hpp"

#include "component/functional/ButtonComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/MovieComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RenderableComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/TextComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/EntityLoaderUtils.hpp"

#include <string>
#include <iostream>

#include "entity/EntityMacro.hpp"

/* Tag loaders */

#define LOAD_DEF_TAG(name) \
void EntityLoaderFactory::Load##name(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader) \
{ rReg.emplace_or_replace< name >(rEntity); }
ALL_TAG_MACRO(LOAD_DEF_TAG)
#undef LOAD_DEF

/* Individual component Loaders */

void EntityLoaderFactory::LoadButtonComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& buttonComp = rReg.get_or_emplace<ButtonComp>(rEntity);
	buttonComp.m_action = token;
}

void EntityLoaderFactory::LoadClickableComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& clickableComp = rReg.get_or_emplace<ClickableComp>(rEntity);
	clickableComp.m_bLeftClicked = false;
	clickableComp.m_bRightClicked = false;
}

void EntityLoaderFactory::LoadHealthComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& healthComp = rReg.get_or_emplace<HealthComp>(rEntity);
	healthComp.m_health = std::stoi(token);
}

void EntityLoaderFactory::LoadInteractableComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	interactableComp.interactionType = token;
}

void EntityLoaderFactory::LoadInteractorComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	interactableComp.interactionType = token;
}

void EntityLoaderFactory::LoadLoadComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& loadComp = rReg.get_or_emplace<LoadComp>(rEntity);
	loadComp.m_filePath = token;
}

void EntityLoaderFactory::LoadMovieComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& movieComp = rReg.get_or_emplace<MovieComp>(rEntity);
	movieComp.m_currentMedia = Media_t::NONE;
}

void EntityLoaderFactory::LoadPositionComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	reader >> token;
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
}

void EntityLoaderFactory::LoadRenderableComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& renderableComp = rReg.get_or_emplace<RenderableComp>(rEntity);
	renderableComp.m_bRendered = false;
}

void EntityLoaderFactory::LoadSizeComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	reader >> token;
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
}

void EntityLoaderFactory::LoadSpriteComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& spriteComp = rReg.get_or_emplace<SpriteComp>(rEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
}

void EntityLoaderFactory::LoadTextComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& textComp = rReg.get_or_emplace<TextComp>(rEntity);
	std::string token;
	reader >> token;
	while (token != ApplicationParameters::k_dialogEscape) { textComp.m_text += token; reader >> token; }
	reader >> token;
}

/* Component aggregate loaders */

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

void EntityLoaderFactory::LoadWidth(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
}

void EntityLoaderFactory::LoadHeight(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
}

void EntityLoaderFactory::LoadFullscreen(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	LoadRenderableComp(rReg, rEntity, reader);
	LoadSpriteComp(rReg, rEntity, reader);
	std::istringstream shallowReader("50 50 100 100");
	LoadPositionComp(rReg, rEntity, shallowReader);
	LoadSizeComp(rReg, rEntity, shallowReader);
}

void EntityLoaderFactory::LoadButton(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	LoadRenderableComp(rReg, rEntity, reader);
	LoadClickableComp(rReg, rEntity, reader);
	LoadButtonComp(rReg, rEntity, reader);
	LoadPositionComp(rReg, rEntity, reader);
	LoadHeight(rReg, rEntity, reader);
	LoadTextComp(rReg, rEntity, reader);

	auto& textComp = rReg.get<TextComp>(rEntity);
	auto& sizeComp = rReg.get<SizeComp>(rEntity);

 	sizeComp.m_size.width = EntityLoaderUtils::GetTextWidth(textComp.m_text, sizeComp.m_size.height);
}

void EntityLoaderFactory::LoadRandomDialog(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	// todo
}

#include "entity/EntityMacroEnd.hpp"

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