#ifndef __SYSTEM_LIST__
#define __SYSTEM_LIST__

#include "system/System.hpp"

#include <entt/fwd.hpp>

#include <list>
#include <memory>

namespace sf { class RenderWindow; }

struct SystemList
{
    static std::list<std::shared_ptr<System>> CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow);
    static std::list<std::shared_ptr<System>> m_pSystemList;
};

#endif