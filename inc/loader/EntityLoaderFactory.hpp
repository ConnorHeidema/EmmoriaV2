#ifndef __ENTITY_LOADER_FACTORY__
#define __ENTITY_LOADER_FACTORY__

#include <entt/entt.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

class EntityLoaderFactory
{
public:
	static void LoadFiles(entt::registry& reg, std::istringstream& reader);
};

#endif