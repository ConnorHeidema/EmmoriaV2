#ifndef __SYSTEM_LIST__
#define __SYSTEM_LIST__

#include "system/System.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <memory>

struct SystemList
{
    static std::list<std::shared_ptr<System>> CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow);
    static std::list<std::shared_ptr<System>> m_pSystemList;
};

#endif