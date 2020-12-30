#include "system/ConfigSys.hpp"

#include "config/ConfigItems.hpp"

int const ConfigSys::updateRate = 60;
std::string const ConfigSys::k_configFileName = "data/Config/config.ini";

ConfigSys::ConfigSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_configUpdateLatch(updateRate)
{
	ConfigItems::LoadConfigFile(k_configFileName);
}

void ConfigSys::Update_()
{
	if (m_configUpdateLatch.CheckLatch())
	{
		ConfigItems::LoadConfigFile(k_configFileName);
	}
}
