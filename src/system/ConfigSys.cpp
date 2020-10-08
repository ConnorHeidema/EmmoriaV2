#include "system/ConfigSys.hpp"

#include "config/ConfigItems.hpp"


int const ConfigSys::updateRate = 60;

ConfigSys::ConfigSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_configUpdateLatch(updateRate)
{ }

void ConfigSys::Update_()
{
	if (m_configUpdateLatch.CheckLatch())
	{
		ConfigItems::m_setConfigItems.clear();
		ConfigItems::LoadConfigFile("data/Config/config.ini");
	}
}
