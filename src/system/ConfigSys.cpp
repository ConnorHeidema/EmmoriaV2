#include "system/ConfigSys.hpp"

#include "config/ConfigItems.hpp"
// todo check if this is needed
#include <entt/entt.hpp>


int const ConfigSys::updateRate = 60;

ConfigSys::ConfigSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_configUpdateLatch(updateRate)
{
	ConfigItems::LoadConfigFile("data/Config/config.ini");
}

void ConfigSys::Update_()
{
	if (m_configUpdateLatch.CheckLatch())
	{
		ConfigItems::LoadConfigFile("data/Config/config.ini");
	}
}
