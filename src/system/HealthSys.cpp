#include "system/HealthSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/HealthComp.hpp"

#include <SFML/Window.hpp>

#include <iostream>

HealthSys::HealthSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void HealthSys::Update_()
{
	m_rReg.view<HealthComp>().each([](auto entity, auto& healthComp) {
		//std::cout <<  std::to_string(healthComp.m_health) << std::endl;
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
