#ifndef __ENTITY_LOADER__
#define __ENTITY_LOADER__

#include "util/Entitymap.hpp"
#include "loader/EntityLoaderFactory.hpp"

#include <entt/entt.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * This class will load things into the registry
 * when scenes transition this will find the entities to load into the new scene
 */
class EntityLoader
{
public:
	EntityLoader();

	void LoadEntities(entt::registry& reg, std::string filename);

};

#endif
