#ifndef __TILE_MAP_SYS__
#define __TILE_MAP_SYS__

#include "system/ISystem.hpp"

#include "core/TileMap.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

class TileMapSys
	: public ISystem
{
public:
	TileMapSys(entt::registry& reg);
	void Update() override;

private:
	entt::registry& m_rReg;

	std::shared_ptr<TileMap> m_pTileMap;
};

#endif