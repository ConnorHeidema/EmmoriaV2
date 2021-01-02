#include "system/System.hpp"

#include "config/ConfigItems.hpp"
#include "util/SystemList.hpp"

#include <SFML/System.hpp>

#include <iostream>
#include <string>

System::System(std::string const& systemName)
		: m_systemName(systemName)
		, m_kLogSystemTime(std::string("LogSystemTime"))
		, m_bEnabled(true)
{
};

System::~System() {}

void System::SetRunning(bool const bRunning)
{
	m_bEnabled = bRunning;
}

std::string System::GetName()
{
	return m_systemName;
}

void System::Update()
{
	if (m_bEnabled)
	{
		if (IsSystemLogged_())
		{
			sf::Clock clock;
			Update_();
			if (clock.getElapsedTime().asMilliseconds() > 0)
			{
				std::cout << std::string("Time spent in ") << m_systemName << " (milliseconds):" << clock.getElapsedTime().asMilliseconds() << std::endl;
			}
		}
		else
		{
			Update_();
		}
	}
}

bool System::IsSystemLogged_()
{
	return ConfigItems::m_setConfigItems.find(m_kLogSystemTime) !=
		ConfigItems::m_setConfigItems.end();
}