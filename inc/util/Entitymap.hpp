#ifndef __ENTITY_MAP__
#define __ENTITY_MAP__

#include "entt/entt.hpp"

#include <unordered_map>
#include <string>

struct Entitymap
{
    static std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> Create_map();
    static std::unordered_map<std::string, void(*)(entt::registry& reg, std::istringstream& line)> const m_entityMap;
};

#endif