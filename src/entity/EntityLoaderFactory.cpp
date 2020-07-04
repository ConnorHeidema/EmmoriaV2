#include "entity/EntityLoaderFactory.hpp"

#include "component/tag/DialogChainComp.hpp"
#include "component/tag/DialogChainFragmentComp.hpp"
#include "component/tag/HealingPadComp.hpp"
#include "component/tag/InteractableComp.hpp"
#include "component/tag/PersistentComp.hpp"
#include "component/tag/PlayerComp.hpp"
#include "component/tag/RandomComp.hpp"

#include "component/functional/ButtonComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/InteractorComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/MovieComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RenderableComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/EntityLoaderUtils.hpp"

#include <string>
#include <iostream>

/* Tag loaders */

#include "entity/EntityMacro.hpp"
#define LOAD_DEF_TAG(name) \
void EntityLoaderFactory::Load##name(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader) \
{ rReg.emplace_or_replace< name >(rEntity); }
ALL_TAG_MACRO(LOAD_DEF_TAG)
#undef LOAD_DEF
#include "entity/EntityMacroEnd.hpp"

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

void EntityLoaderFactory::LoadInteractorComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& interactorComp = rReg.get_or_emplace<InteractorComp>(rEntity);
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
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_widthAdjustment;
	reader >> token;
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_heightAdjustment;
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
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_widthAdjustment;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_heightAdjustment;
}

void EntityLoaderFactory::LoadSpriteComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& spriteComp = rReg.get_or_emplace<SpriteComp>(rEntity);
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ApplicationParameters::k_pictureExt;
}

void EntityLoaderFactory::LoadTextComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& textComp = rReg.get_or_emplace<TextComp>(rEntity);
	std::string token;
	reader >> token;
	while (token != ApplicationParameters::k_dialogEscape) { textComp.m_text += token + " "; reader >> token; }
	textComp.m_text.pop_back();
	reader >> token;
}

void EntityLoaderFactory::LoadTileMapComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	// TODO
	auto& tileMapComp = rReg.get_or_emplace<TilemapComp>(rEntity);
	std::string token;
	reader >> token;
	tileMapComp.m_tilemapIndex = 0;
}

/* Component aggregate loaders */

void EntityLoaderFactory::LoadXposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_widthAdjustment;
}

void EntityLoaderFactory::LoadYposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_heightAdjustment;
}

void EntityLoaderFactory::LoadWidth(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_widthAdjustment;
}

void EntityLoaderFactory::LoadHeight(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_heightAdjustment;
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
 	rReg.emplace<DialogChainComp>(rEntity);
 	rReg.emplace<RandomComp>(rEntity);
	LoadHeight(rReg, rEntity, reader);
	LoadTextComp(rReg, rEntity, reader);
}
