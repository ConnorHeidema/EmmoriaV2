#ifndef __SYSTEM_LIST__
#define __SYSTEM_LIST__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <memory>

struct SystemList
{
    static std::list<std::shared_ptr<ISystem>> CreateSystemList(entt::registry& m_reg, sf::RenderWindow& m_renderWindow);
    static std::list<std::shared_ptr<ISystem>> m_pSystemList;
};

#endif