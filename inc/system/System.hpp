#ifndef __SYSTEM__
#define __SYSTEM__

#include "config/ConfigItems.hpp"

#include <SFML/Window.hpp>

#include <string>

/**
 * Purpose:
 * 	This abstract class acts as a facade for all systems to allow each system
 * 	to be disabled with a config setting.
 */
class System
{
public:
	System(std::string systemConfigItem)
		: m_systemConfigItem(systemConfigItem)
	{};

	virtual ~System() {};
	void Update()
	{
		if (IsSystemEnabled_()) { Update_(); }
	}

private:
	virtual void Update_() = 0;

	bool IsSystemEnabled_()
	{
		return ConfigItems::m_setConfigItems.find(m_systemConfigItem) ==
			ConfigItems::m_setConfigItems.end();
	}

	std::string const m_systemConfigItem;
};

#endif