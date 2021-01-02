#ifndef __SYSTEM_LIST__
#define __SYSTEM_LIST__

#include "system/System.hpp"

#include <entt/fwd.hpp>

#include <vector>
#include <memory>

namespace sf { class RenderWindow; }

struct SystemList
{
    static std::vector<std::shared_ptr<System>> CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow);
    static std::vector<std::shared_ptr<System>> m_pSystemList;
};

#include "system/SystemMacro.hpp"
enum class SystemId_t { DO_MACRO_FOR_ALL_SYSTEMS(DEFINE_SYSTEM_ENUM, DEFINE_SYSTEM_ENUM) };
#include "system/SystemMacroEnd.hpp"

#endif