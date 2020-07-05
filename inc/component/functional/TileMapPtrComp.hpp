#ifndef __TILE_MAP_PTR_COMP__
#define __TILE_MAP_PTR_COMP__

#include "core/TileMap.hpp"

#include <memory>

/**
 * This component should be added to any tilemap that has been created
 */
struct TileMapPtrComp
{
	std::shared_ptr<TileMap> m_pTileMap;
};

#endif
