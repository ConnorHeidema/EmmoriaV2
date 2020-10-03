#ifndef __SYSTEM__
#define __SYSTEM__

#include <string>

#include "config/ConfigItems.hpp"

class System
{
public:
	System(std::string systemConfigItem)
		: m_systemConfigItem(systemConfigItem)
	{};
	virtual ~System() {};
	void Update()
	{
		if (ConfigItems::m_setConfigItems.find(m_systemConfigItem) == ConfigItems::m_setConfigItems.end())
		{
			Update_();
		}
	}

private:
	virtual void Update_() = 0;

	std::string m_systemConfigItem;
};

#endif