#include "entity/EntityLoaderFactory.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/ButtonComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/InteractableComp.hpp"
#include "component/functional/InteractorComp.hpp"
#include "component/functional/LastPositionComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/MovieComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/RenderableComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapComp.hpp"
#include "component/functional/TileMapPieceComp.hpp"
#include "component/functional/LocationComp.hpp"
#include "component/functional/RotationComp.hpp"

#include "component/InteractStringMap.hpp"

#include "TileMap/TileMapIndexes.hpp"

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

void EntityLoaderFactory::LoadInteractableComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	try
	{
		interactableComp.m_interactType.emplace_back(InteractStringMap::s_interactStringToType.at(token));
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load interactable " << token << " parameter." << std::endl;
	}
}

void EntityLoaderFactory::LoadInteractorComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& interactorComp = rReg.get_or_emplace<InteractorComp>(rEntity);
	try
	{
		interactorComp.m_interactType.emplace_back(InteractStringMap::s_interactStringToType.at(token));
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load interactor " << token << " parameter." << std::endl;
	}
}

void EntityLoaderFactory::LoadLastPositionComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	auto& positionComp = rReg.get_or_emplace<LastPositionComp>(rEntity);
	reader >> token;
	positionComp.m_lastPosition.x = float(std::stoi(token) * ApplicationParameters::k_widthAdjustment);
	reader >> token;
	positionComp.m_lastPosition.y = float(std::stoi(token) * ApplicationParameters::k_heightAdjustment);
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
	float x = 0;
	float y = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		x = float(locationComp.xLocation * ApplicationParameters::k_rightOfScreen);
		y = float(locationComp.yLocation * ApplicationParameters::k_bottomOfScreen);
	});

	positionComp.m_position.x = float(std::stoi(token) * ApplicationParameters::k_widthAdjustment + x);
	reader >> token;
	positionComp.m_position.y = float(std::stoi(token) * ApplicationParameters::k_heightAdjustment + y);
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
	auto& tileMapComp = rReg.get_or_emplace<TileMapComp>(rEntity);
	std::string token;
	reader >> token;
	tileMapComp.m_tileMapBase = token;
}

void EntityLoaderFactory::LoadTileMapPieceComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& tileMapPieceComp = rReg.get_or_emplace<TileMapPieceComp>(rEntity);
	std::string token;
	reader >> token;
	try
	{
		tileMapPieceComp.m_index = TileMapIndexes::stringToEnumTileMap.at(token);
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load tilemap piece: " << token << std::endl;
	}
}

void EntityLoaderFactory::LoadLocationComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.clear<LocationComp>();
	auto& locationComp = rReg.get_or_emplace<LocationComp>(rEntity);
	std::string token;
	reader >> token;
	locationComp.area = token;
	reader >> token;
	locationComp.xLocation = std::stoi(token);
	reader >> token;
	locationComp.yLocation = std::stoi(token);
	std::cout << "Loaded location comp" << std::endl;
}

void EntityLoaderFactory::LoadRotationComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;
	auto& rotationComp = rReg.get_or_emplace<RotationComp>(rEntity);
	rotationComp.m_angle = std::stof(token);
}

void EntityLoaderFactory::LoadXposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;

	float x = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		x = float(locationComp.xLocation * ApplicationParameters::k_rightOfScreen);
	});

	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.x = float(std::stoi(token) * ApplicationParameters::k_widthAdjustment + x);
}

void EntityLoaderFactory::LoadYposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	reader >> token;

	float y = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		y = float(locationComp.xLocation * ApplicationParameters::k_bottomOfScreen);
	});

	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.y = float(std::stoi(token) * ApplicationParameters::k_heightAdjustment + y);
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
	auto& spriteComp = rReg.get<SpriteComp>(rEntity);

	spriteComp.m_height = 1080;
	spriteComp.m_width = 1920;

	std::string widthUnits = std::to_string(ApplicationParameters::k_widthUnits / 2);
	std::string heightUnits = std::to_string(ApplicationParameters::k_heightUnits / 2);
	std::string widthScreen = std::to_string(ApplicationParameters::k_widthUnits);
	std::string heightScreen = std::to_string(ApplicationParameters::k_heightUnits);
	std::istringstream shallowReader(widthUnits + " " + heightUnits + " " + widthScreen + " " + heightScreen);
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

void EntityLoaderFactory::LoadIndexedPosition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	std::string token;
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);

	reader >> token;
	positionComp.m_position.x = float(std::stoi(token) * ApplicationParameters::k_widthAdjustment);
	reader >> token;
	positionComp.m_position.y = float(std::stoi(token) * ApplicationParameters::k_heightAdjustment);

	float x = 0;
	float y = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		x = locationComp.xLocation * ApplicationParameters::k_rightOfScreen;
		y = locationComp.yLocation * ApplicationParameters::k_bottomOfScreen;
	});

	positionComp.m_position.x =
		float((positionComp.m_position.x + ApplicationParameters::k_widthAdjustment/2) * ApplicationParameters::k_tileUnitSize + x);
	positionComp.m_position.y =
		float((positionComp.m_position.y + ApplicationParameters::k_heightAdjustment/2) * ApplicationParameters::k_tileUnitSize + y);
	auto& sizeComp = rReg.get_or_emplace<SizeComp>(rEntity);
	sizeComp.m_size.width = ApplicationParameters::k_tileScreenWidthSize;
	sizeComp.m_size.height = ApplicationParameters::k_tileScreenHeightSize;
}

void EntityLoaderFactory::LoadWallTile(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.emplace<WallComp>(rEntity);
 	rReg.emplace<RenderableComp>(rEntity);
	LoadTileMapPieceComp(rReg, rEntity, reader);
	LoadIndexedPosition(rReg, rEntity, reader);
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	interactableComp.m_interactType.emplace_back(InteractType_t::WallComp_t);
}