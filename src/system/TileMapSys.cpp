#include "system/TileMapSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/functional/TileMapComp.hpp"
#include "component/functional/TileMapPieceComp.hpp"
#include "component/functional/PositionComp.hpp"

TileMapSys::TileMapSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rReg(rReg)
	, m_tileMap()
	, m_rRenderWindow(rRenderWindow)

{
}

void TileMapSys::Update()
{

	m_rReg.view<TileMapComp>().each([&](auto entity, auto& tileMapComp)
	{
		m_tileMap.m_fileToUse = tileMapComp.m_tileMapBase;
		m_tileMap.m_tileset.loadFromFile(ApplicationParameters::k_tilemapPath + m_tileMap.m_fileToUse + ApplicationParameters::k_pictureExt);
	});

	m_rReg.view<TileMapPieceComp, PositionComp>().each([&](auto entity, auto& tileMapPieceComp, auto& positionComp)
	{
		m_tileMap.PopulateQuad(positionComp.m_position.x, positionComp.m_position.y, tileMapPieceComp.m_index);
	});
	m_rRenderWindow.draw(m_tileMap);
}