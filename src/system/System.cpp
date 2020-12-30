#include "system/System.hpp"

#include "config/ConfigItems.hpp"

#include <SFML/System.hpp>

#include <iostream>
#include <string>

System::System(std::string const& systemConfigItem)
		: m_systemConfigItem(systemConfigItem)
		, m_kLogSystemTime(std::string("LogSystemTime"))
{};

System::~System() {}

void System::Update()
{
	if (IsSystemEnabled_())
	{
		if (IsSystemLogged_())
		{
			sf::Clock clock;
			Update_();
			if (clock.getElapsedTime().asMilliseconds() > 0)
			{
				std::cout << std::string("Time spent in ") << m_systemConfigItem.substr(7) << " (milliseconds):" << clock.getElapsedTime().asMilliseconds() << std::endl;
			}
		}
		else
		{
			Update_();
		}
	}
}

bool System::IsSystemEnabled_()
{
	return ConfigItems::m_setConfigItems.find(m_systemConfigItem) ==
		ConfigItems::m_setConfigItems.end();
}

bool System::IsSystemLogged_()
{
	return ConfigItems::m_setConfigItems.find(m_kLogSystemTime) !=
		ConfigItems::m_setConfigItems.end();
}