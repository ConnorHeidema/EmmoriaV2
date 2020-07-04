#include "system/HealthSys.hpp"

#include "component/tag/PlayerComp.hpp"

#include "component/functional/HealthComp.hpp"

#include <SFML/Window.hpp>

#include <iostream>

HealthSys::HealthSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void HealthSys::Update()
{
	m_rReg.view<HealthComp>().each([](auto entity, auto& healthComp) {
		std::cout <<  std::to_string(healthComp.m_health) << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			healthComp.m_health -= 1;
		}
	});

	m_rReg.view<PlayerComp, HealthComp>().each([&](auto entity, auto& healthComp) {

		if (healthComp.m_health == 0)
		{
			std::cout << "game over" << std::endl;
			m_rReg.destroy(entity);
		}
	});
}
