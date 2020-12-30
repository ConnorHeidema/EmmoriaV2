#include "system/SwitchSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/SwitchComp.hpp"
#include "component/functional/DoorComp.hpp"

#include <entt/entt.hpp>

SwitchSys::SwitchSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void SwitchSys::Update_()
{
	m_rReg.view<SwitchComp>().each([&](auto entity, auto& switchComp)
	{
		m_rReg.view<DoorComp>().each([&](auto entity, auto& doorComp)
		{
			if (switchComp.m_action == doorComp.m_action)
			{
				doorComp.m_bOpen = switchComp.m_bPressed;
			}
		});
		switchComp.m_bPressed = false;
	});
}
