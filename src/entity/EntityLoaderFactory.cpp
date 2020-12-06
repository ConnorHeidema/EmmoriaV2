#include "entity/EntityLoaderFactory.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SwitchComp.hpp"
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
#include "component/functional/SpeedComp.hpp"
#include "component/functional/TrackingComp.hpp"
#include "component/functional/DoorComp.hpp"
#include "component/functional/stats/MaxHealthComp.hpp"

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

/* Individual functional component Loaders */

#define SIMPLE_FUNCTIONAL_NO_PARAMETER(name) \
	void EntityLoaderFactory::Load## name ## Comp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader) \
	{ \
		rReg.get_or_emplace< name ## Comp>(rEntity); \
	}

SIMPLE_FUNCTIONAL_NO_PARAMETER(Clickable)
SIMPLE_FUNCTIONAL_NO_PARAMETER(Switch)
SIMPLE_FUNCTIONAL_NO_PARAMETER(Door)
SIMPLE_FUNCTIONAL_NO_PARAMETER(Movie)
SIMPLE_FUNCTIONAL_NO_PARAMETER(Renderable)

void EntityLoaderFactory::LoadButtonComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<ButtonComp>(rEntity).m_action = ReadTokenList_(1, reader).at(0);
}

void EntityLoaderFactory::LoadMaxHealthComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<MaxHealthComp>(rEntity).m_maxHealth = std::stoi(ReadTokenList_(1, reader).at(0));
}

void EntityLoaderFactory::LoadHealthComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<HealthComp>(rEntity).m_health = std::stoi(ReadTokenList_(1, reader).at(0));
}

void EntityLoaderFactory::LoadInteractableComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(1, reader);
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	try
	{
		interactableComp.m_interactTypeList.insert(InteractStringMap::s_interactStringToType.at(tokens.at(0)));
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load interactable " << tokens.at(0) << " parameter." << std::endl;
	}
}

void EntityLoaderFactory::LoadInteractorComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(1, reader);
	auto& interactorComp = rReg.get_or_emplace<InteractorComp>(rEntity);
	try
	{
		interactorComp.m_interactTypeList.insert(InteractStringMap::s_interactStringToType.at(tokens.at(0)));
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load interactor " << tokens.at(0) << " parameter." << std::endl;
	}
}

void EntityLoaderFactory::LoadLastPositionComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(2, reader);
	auto& position = rReg.get_or_emplace<LastPositionComp>(rEntity).m_lastPosition;
	position.x = float(std::stoi(tokens.at(0)) * ApplicationParameters::k_widthAdjustment);
	position.y = float(std::stoi(tokens.at(1)) * ApplicationParameters::k_heightAdjustment);
}

void EntityLoaderFactory::LoadLoadComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<LoadComp>(rEntity).m_filePath = ReadTokenList_(1, reader).at(0);
}

void EntityLoaderFactory::LoadPositionComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& position = rReg.get_or_emplace<PositionComp>(rEntity).m_position;
	float x = 0;
	float y = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		x = float(locationComp.xLocation * ApplicationParameters::k_rightOfScreen);
		y = float(locationComp.yLocation * ApplicationParameters::k_bottomOfScreen);
	});
	auto tokens = ReadTokenList_(2, reader);
	position.x = float(std::stoi(tokens.at(0)) * ApplicationParameters::k_widthAdjustment + x);
	position.y = float(std::stoi(tokens.at(1)) * ApplicationParameters::k_heightAdjustment + y);
}

void EntityLoaderFactory::LoadSizeComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(2, reader);
	auto& size = rReg.get_or_emplace<SizeComp>(rEntity).m_size;
	size.width = std::stoi(tokens.at(0)) * ApplicationParameters::k_widthAdjustment;
	size.height = std::stoi(tokens.at(1)) * ApplicationParameters::k_heightAdjustment;
}

void EntityLoaderFactory::LoadSpriteComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<SpriteComp>(rEntity).m_filePath =
		ApplicationParameters::k_spritePath +
		ReadTokenList_(1, reader).at(0) +
		ApplicationParameters::k_pictureExt;
}

void EntityLoaderFactory::LoadTextComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& text = rReg.get_or_emplace<TextComp>(rEntity).m_text;
	std::string token;
	reader >> token;
	while (token != ApplicationParameters::k_dialogEscape) { text += token + " "; reader >> token; }
	text.pop_back();
	reader >> token;
}

void EntityLoaderFactory::LoadTrackingComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<TrackingComp>(rEntity).m_sight = std::stoi(ReadTokenList_(1, reader)[0]);
}

void EntityLoaderFactory::LoadSpeedComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<SpeedComp>(rEntity).m_speed = std::stoi(ReadTokenList_(1, reader)[0]);
}

void EntityLoaderFactory::LoadTileMapComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<TileMapComp>(rEntity).m_tileMapBase = ReadTokenList_(1, reader).at(0);
}

void EntityLoaderFactory::LoadTileMapPieceComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& tileMapPieceComp = rReg.get_or_emplace<TileMapPieceComp>(rEntity);
	auto tokens = ReadTokenList_(1, reader);
	try
	{
		tileMapPieceComp.m_index = TileMapIndexes::stringToEnumTileMap.at(tokens.at(0));
	}
	catch (std::out_of_range /*e*/)
	{
		std::cout << "Could not load tilemap piece: " << tokens.at(0) << std::endl;
	}
}

void EntityLoaderFactory::LoadLocationComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(3, reader);
	rReg.clear<LocationComp>();
	auto& locationComp = rReg.get_or_emplace<LocationComp>(rEntity);
	locationComp.area = tokens.at(0);
	locationComp.xLocation = std::stoi(tokens.at(1));
	locationComp.yLocation = std::stoi(tokens.at(2));
	std::cout << "Loaded location comp" << std::endl;
}

void EntityLoaderFactory::LoadRotationComp(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<RotationComp>(rEntity).m_angle = std::stof(ReadTokenList_(1, reader).at(0));
}

void EntityLoaderFactory::LoadXposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(1, reader);

	float x = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		x = float(locationComp.xLocation * ApplicationParameters::k_rightOfScreen);
	});

	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.x = float(std::stoi(tokens.at(0)) * ApplicationParameters::k_widthAdjustment + x);
}

void EntityLoaderFactory::LoadYposition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto tokens = ReadTokenList_(1, reader);

	float y = 0;
	rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
	{
		y = float(locationComp.xLocation * ApplicationParameters::k_bottomOfScreen);
	});

	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	positionComp.m_position.y = float(std::stoi(tokens.at(0)) * ApplicationParameters::k_heightAdjustment + y);
}

void EntityLoaderFactory::LoadWidth(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<SizeComp>(rEntity).m_size.width =
		std::stoi(ReadTokenList_(1, reader).at(0)) * ApplicationParameters::k_widthAdjustment;
}

void EntityLoaderFactory::LoadHeight(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.get_or_emplace<SizeComp>(rEntity).m_size.height =
		std::stoi(ReadTokenList_(1, reader).at(0)) * ApplicationParameters::k_heightAdjustment;
}

void EntityLoaderFactory::LoadFullscreen(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	LoadRenderableComp(rReg, rEntity, reader);
	LoadSpriteComp(rReg, rEntity, reader);
	auto& spriteComp = rReg.get<SpriteComp>(rEntity);

	spriteComp.m_width = ApplicationParameters::k_screenWidth;
	spriteComp.m_height = ApplicationParameters::k_screenHeight;

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

void EntityLoaderFactory::LoadBottomDialog(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
 	rReg.emplace<DialogChainComp>(rEntity);
	rReg.emplace<StructuredDialogComp>(rEntity);
	LoadHeight(rReg, rEntity, reader);
	LoadTextComp(rReg, rEntity, reader);
}

void EntityLoaderFactory::LoadIndexedPosition(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	auto& positionComp = rReg.get_or_emplace<PositionComp>(rEntity);
	auto tokens = ReadTokenList_(2, reader);
	positionComp.m_position.x = float(std::stoi(tokens.at(0)) * ApplicationParameters::k_widthAdjustment);
	positionComp.m_position.y = float(std::stoi(tokens.at(1)) * ApplicationParameters::k_heightAdjustment);

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
 	rReg.emplace<DeloadableComp>(rEntity);
	LoadTileMapPieceComp(rReg, rEntity, reader);
	LoadIndexedPosition(rReg, rEntity, reader);
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	interactableComp.m_interactTypeList.insert(InteractType_t::WallComp_t);
}

void EntityLoaderFactory::LoadHoleTile(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.emplace<HoleComp>(rEntity);
 	rReg.emplace<RenderableComp>(rEntity);
 	rReg.emplace<DeloadableComp>(rEntity);
	LoadTileMapPieceComp(rReg, rEntity, reader);
	LoadIndexedPosition(rReg, rEntity, reader);
	auto& interactableComp = rReg.get_or_emplace<InteractableComp>(rEntity);
	interactableComp.m_interactTypeList.insert(InteractType_t::HoleComp_t);
}

void EntityLoaderFactory::LoadBlob(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader)
{
	rReg.emplace<BlobComp>(rEntity);
	rReg.emplace<RenderableComp>(rEntity);
	rReg.emplace<DeloadableComp>(rEntity);
	rReg.emplace<WallInteractorComp>(rEntity);
	rReg.emplace<WeightComp>(rEntity);

	LoadPositionComp(rReg, rEntity, reader);
	auto& size = rReg.get_or_emplace<SizeComp>(rEntity).m_size;
	size.width = 5 * ApplicationParameters::k_widthAdjustment;
	size.height = 5 * ApplicationParameters::k_heightAdjustment;

	rReg.get_or_emplace<SpeedComp>(rEntity).m_speed = 1;
	rReg.get_or_emplace<TrackingComp>(rEntity).m_sight = 300;

	auto& interactables = rReg.get_or_emplace<InteractableComp>(rEntity).m_interactTypeList;
	interactables.insert(InteractStringMap::s_interactStringToType.at("BlobComp"));
	interactables.insert(InteractStringMap::s_interactStringToType.at("WeightComp"));
	auto& interactors = rReg.get_or_emplace<InteractorComp>(rEntity).m_interactTypeList;
	interactors.insert(InteractStringMap::s_interactStringToType.at("WallInteractorComp"));
	interactors.insert(InteractStringMap::s_interactStringToType.at("BlobComp"));

	rReg.get_or_emplace<HealthComp>(rEntity).m_health = 10;

	rReg.get_or_emplace<SpriteComp>(rEntity).m_filePath =
		ApplicationParameters::k_spritePath + std::string("Blob") + ApplicationParameters::k_pictureExt;
}

std::vector<std::string> EntityLoaderFactory::ReadTokenList_(int wordsToIngest, std::istringstream& reader)
{
	std::string token;
	std::vector<std::string> tokenList;
	for (int i = 0; i < wordsToIngest; i++)
	{
		reader >> token;
		tokenList.push_back(token);
	}
	return tokenList;
}
