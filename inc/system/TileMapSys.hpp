#ifndef __TILE_MAP_SYS__
#define __TILE_MAP_SYS__

#include "system/ISystem.hpp"

#include "core/TileMap.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

class TileMapSys
	: public ISystem
{
public:
	TileMapSys(entt::registry& reg, sf::RenderWindow& rRenderWindow);
	void Update() override;

private:
	entt::registry& m_rReg;
	TileMap m_tileMap;
	sf::RenderWindow& m_rRenderWindow;
};

#endif