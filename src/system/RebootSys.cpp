#include "system/RebootSys.hpp"

#include "component/tag/AllTagComp.hpp"
#include <entt/entt.hpp>

#include <iostream>

RebootSys::RebootSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{}

void RebootSys::Update_()
{
	if (ConfigItems::m_setConfigItems.find("TrackEntityCount") != ConfigItems::m_setConfigItems.end())
	{
		std::cout << "Current number of entities:" << m_rReg.alive() << std::endl;
	}
	bool bReboot = false;
	m_rReg.view<RebootComp>().each([&](auto entity)
	{
		bReboot = true;
	});
	if (bReboot)
	{
		m_rReg.clear();
		auto animationEntity = m_rReg.create();
		m_rReg.emplace_or_replace<AnimationRebootComp>(animationEntity);
	}
}
