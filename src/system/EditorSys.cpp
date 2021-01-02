#include "system/EditorSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/LocationComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapPtrComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/DialogComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/stats/MaxHealthComp.hpp"
#include "component/functional/SoundComp.hpp"

#include "util/Mediamap.hpp"
#include "util/ApplicationParameters.hpp"
#include "util/Helper.hpp"
#include "util/TextureContainer.hpp"
#include "util/FontContainer.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include <entt/entt.hpp>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <math.h>

#include "config/ConfigItems.hpp"
#include "util/SystemList.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

EditorSys::EditorSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_thingsToPlaceDownSet()
	, m_currentSetIndex(0)
{ }

// This needs to parse a file based on the location, open that file and when the user scrolls allow the user to place things
// in a certain file onto the screen. It needs to tell whether what you are placing is on a tilemap or not.
// Finally it should write those contents to a temp file and allow it to be saved if the user selects an action.
// This should only work if a certain config item is set to true AllowEditing
void EditorSys::Update_()
{
	if (ConfigItems::m_setConfigItems.find("EditorMode") == ConfigItems::m_setConfigItems.end())
	{
		return;
	}

	DisableUnusefulSystems_();
	UpdateSetOfOptions_();
	GetNewScrollPosition_();
	CreateCursor_();
}

void EditorSys::WriteTextureLineToTemp_(int textureIndex)
{
	// checks if texture exists at point, if one does, it is overriden
}

void EditorSys::WriteSpriteLineToTemp_(std::string spriteName)
{
	// checks if sprite exists in approximate location
	// if not, adds to file
	// if a different sprite exists there, replace it
}

void EditorSys::GetNewScrollPosition_()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_currentSetIndex = (m_currentSetIndex + 1) % m_thingsToPlaceDownSet.size();
		std::cout << m_thingsToPlaceDownSet[m_currentSetIndex] << std::endl;
		std::cout << m_currentSetIndex << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_currentSetIndex = (m_currentSetIndex == 0 ? m_thingsToPlaceDownSet.size() - 1 : m_currentSetIndex - 1);
		std::cout << m_thingsToPlaceDownSet[m_currentSetIndex] << std::endl;
		std::cout << m_currentSetIndex << std::endl;
	}
}

void EditorSys::DisableUnusefulSystems_()
{
	// I should make a system to disable systems that runs first every frame and any system can pass
	// it an entity specifying the sytems to disable on the next frame
	SystemList::m_pSystemList[static_cast<int>(SystemId_t::Animation_t)]->SetRunning(false);
	SystemList::m_pSystemList[static_cast<int>(SystemId_t::Bow_t)]->SetRunning(false);
	SystemList::m_pSystemList[static_cast<int>(SystemId_t::Health_t)]->SetRunning(false);
	SystemList::m_pSystemList[static_cast<int>(SystemId_t::Interacting_t)]->SetRunning(false);
}

void EditorSys::UpdateSetOfOptions_()
{
	m_thingsToPlaceDownSet.clear();
	std::string m_currentLocation = "";
	m_rReg.view<LocationComp>().each([&m_currentLocation](auto entity, auto& locationComp)
	{
		m_currentLocation = locationComp.area;
	});

	std::string line;
	std::ifstream areaFile(std::string("data/builder/") + m_currentLocation);
  	if (areaFile.is_open())
	{
		while (getline(areaFile, line))
		{
			m_thingsToPlaceDownSet.emplace_back(line);
		}
		areaFile.close();
	}
	std::ifstream allFile("data/builder/All");
  	if (allFile.is_open())
	{
		while (getline(allFile, line))
		{
			m_thingsToPlaceDownSet.emplace_back(line);
		}
		allFile.close();
	}
}

int EditorSys::GetTextureSubIndex_()
{
    std::istringstream iss(m_thingsToPlaceDownSet[m_currentSetIndex]);
    do
    {
        std::string subs;
        iss >> subs;
		if (TileMapIndexes::stringToEnumTileMap.find(subs) != TileMapIndexes::stringToEnumTileMap.end())
			return TileMapIndexes::stringToEnumTileMap.at(subs);

    } while (iss);
	return -1;
}

std::string EditorSys::GetSpriteName_()
{
    std::istringstream iss(m_thingsToPlaceDownSet[m_currentSetIndex]);
    do
    {
        std::string subs;
        iss >> subs;
		std::ifstream f(ApplicationParameters::k_spritePath + subs + ApplicationParameters::k_pictureExt);
		if (f.good())
			return subs;
    } while (iss);
	return "";
}

void EditorSys::CreateCursor_()
{
	m_rReg.view<CursorImageComp>().each([&](auto entity)
	{
		m_rReg.destroy(entity);
	});

	if (sf::Mouse::getPosition().y > ApplicationParameters::k_bottomOfScreen)
		return;

	int textureIndex = GetTextureSubIndex_();
	std::string spriteName = GetSpriteName_();
	if (spriteName != "")
	{
		auto size = Size{100, 100};
		auto genericSprite = sf::RectangleShape(sf::Vector2f(size.width, size.height));
		if (sf::Mouse::getPosition().y >= ApplicationParameters::k_bottomOfScreen)
			return;

		auto entity = m_rReg.create();
		m_rReg.emplace<CursorImageComp>(entity);
		m_rReg.emplace<RenderableComp>(entity);
		auto& posComp = m_rReg.emplace<PositionComp>(entity);
		posComp.m_position.x = sf::Mouse::getPosition().x;
		posComp.m_position.y = sf::Mouse::getPosition().y;

		auto& sizeComp = m_rReg.emplace<SizeComp>(entity);
		sizeComp.m_size.width = ApplicationParameters::k_widthAdjustment * 5;
		sizeComp.m_size.height = ApplicationParameters::k_heightAdjustment * 5;
		auto& spriteComp = m_rReg.emplace<SpriteComp>(entity);
		spriteComp.m_filePath = ApplicationParameters::k_spritePath + std::string(spriteName) + ApplicationParameters::k_pictureExt;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			WriteSpriteLineToTemp_(spriteName);
		}
	}
	else if (textureIndex != -1)
	{
		auto size = Size{100, 100};
		auto genericSprite = sf::RectangleShape(sf::Vector2f(size.width, size.height));

		auto entity = m_rReg.create();
		m_rReg.emplace<CursorImageComp>(entity);
		m_rReg.emplace<RenderableComp>(entity);
		auto& posComp = m_rReg.emplace<PositionComp>(entity);
		posComp.m_position.x = int(sf::Mouse::getPosition().x / ApplicationParameters::k_widthAdjustment / ApplicationParameters::k_tileUnitSize) * ApplicationParameters::k_tileScreenWidthSize;
		posComp.m_position.y = int(sf::Mouse::getPosition().y / ApplicationParameters::k_heightAdjustment / ApplicationParameters::k_tileUnitSize) * ApplicationParameters::k_tileScreenHeightSize;
		posComp.m_position.x += ApplicationParameters::k_tileScreenWidthSize / 2;
		posComp.m_position.y += ApplicationParameters::k_tileScreenHeightSize / 2;

		auto& sizeComp = m_rReg.emplace<SizeComp>(entity);
		sizeComp.m_size.width = ApplicationParameters::k_widthAdjustment * ApplicationParameters::k_tileUnitSize;
		sizeComp.m_size.height = ApplicationParameters::k_heightAdjustment * ApplicationParameters::k_tileUnitSize;
		auto& spriteComp = m_rReg.emplace<SpriteComp>(entity);
		spriteComp.m_spriteIndex = textureIndex;
		m_rReg.view<LocationComp>().each([&](auto entity, auto& locationComp)
		{
			spriteComp.m_filePath = ApplicationParameters::k_spritePath + "tilemap/" + locationComp.area + ApplicationParameters::k_pictureExt;
		});
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			WriteTextureLineToTemp_(textureIndex);
		}
	}
}
