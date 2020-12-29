#include "system/TileMapSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/functional/TileMapComp.hpp"
#include "component/functional/TileMapPieceComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/TileMapPtrComp.hpp"
#include "component/functional/RenderableComp.hpp"

#include <entt/entt.hpp>

TileMapSys::TileMapSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_pTileMap(std::make_shared<TileMap>())
{
}

void TileMapSys::Update_()
{
	m_rReg.view<TileMapComp>().each([&](auto entity, auto& tileMapComp)
	{
		m_pTileMap->m_fileToUse = tileMapComp.m_tileMapBase;
		m_pTileMap->m_tileset.loadFromFile(ApplicationParameters::k_tilemapPath + m_pTileMap->m_fileToUse + ApplicationParameters::k_pictureExt);
		auto& tileMapPtrComp = m_rReg.get_or_emplace<TileMapPtrComp>(entity);
		tileMapPtrComp.m_pTileMap = m_pTileMap;
	});

	m_rReg.view<TileMapPieceComp, PositionComp, RenderableComp>().each([&](auto entity, auto& tileMapPieceComp, auto& positionComp, auto& renderableComp)
	{
		m_pTileMap->PopulateQuad(
			int(positionComp.m_position.x) % ApplicationParameters::k_rightOfScreen,
			int(positionComp.m_position.y) % ApplicationParameters::k_bottomOfScreen,
			tileMapPieceComp.m_index);
	});
}
