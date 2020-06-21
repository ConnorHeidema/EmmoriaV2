#include "util/Entitymap.hpp"
#include "entity/EntityLoaderFactory.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> Entitymap::Create_map()
{
	#define LOADER_TYPE(name) m[#name] = EntityLoaderFactory::Load##name;
		std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> m;
		LOADER_TYPE(File);
		LOADER_TYPE(Background);
		LOADER_TYPE(Dialog)
	#undef LOADER_TYPE

	return m;
}

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> const Entitymap::m_entityMap =  Entitymap::Create_map();
