#ifndef __ENTITY_MAP__
#define __ENTITY_MAP__

#include "entt/entt.hpp"

#include <unordered_map>
#include <string>

using fnEntityfactory = void(*)(entt::registry& rReg, entt::entity& rEntity, std::istringstream& reader);

struct Entitymap
{
    static std::unordered_map<std::string, fnEntityfactory> Create_map();
    static std::unordered_map<std::string, fnEntityfactory> const m_entityMap;
};

#endif