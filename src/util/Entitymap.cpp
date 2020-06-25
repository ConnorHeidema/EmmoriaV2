#include "util/Entitymap.hpp"
#include "entity/EntityLoaderFactory.hpp"

#include "entity/EntityMacro.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> Entitymap::Create_map()
{
	#define LOADER_TYPE(name) m[#name] = EntityLoaderFactory::Load##name;
		std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> m;
	ALL_ENTITY_MACRO(LOADER_TYPE)
	#undef LOADER_TYPE

	return m;
}

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> const Entitymap::m_entityMap =  Entitymap::Create_map();

#include "entity/EntityMacroEnd.hpp"