#include "system/HealthSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/HealthComp.hpp"

#include <SFML/Window.hpp>

#include <iostream>
#include <entt/entt.hpp>

HealthSys::HealthSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void HealthSys::Update_()
{
	m_rReg.view<PlayerComp, HealthComp>().each([&](auto entity, auto& healthComp) {
		if (healthComp.m_health <= 0)
		{
			auto reboot = m_rReg.create();
			m_rReg.emplace<RebootComp>(reboot);
		}
	});

	m_rReg.view<HealthComp>().each([&](auto entity, auto& healthComp) {
		if (healthComp.m_health <= 0)
		{
			m_rReg.destroy(entity);
		}
	});

}
