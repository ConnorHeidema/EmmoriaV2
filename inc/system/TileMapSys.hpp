#ifndef __TILE_MAP_SYS__
#define __TILE_MAP_SYS__

#include "system/System.hpp"

#include "core/TileMap.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

class TileMapSys
	: public System
{
public:
	TileMapSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;

	entt::registry& m_rReg;

	std::shared_ptr<TileMap> m_pTileMap;
};

#endif