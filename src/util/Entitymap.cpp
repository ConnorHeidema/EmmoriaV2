#include "util/Entitymap.hpp"
#include "entity/EntityLoaderFactory.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> Entitymap::Create_map()
{
	std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> m;
	m["file"] = EntityLoaderFactory::LoadFiles;
	m["background"] = EntityLoaderFactory::LoadBackground;
	return m;
}

std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> const Entitymap::m_entityMap =  Entitymap::Create_map();
