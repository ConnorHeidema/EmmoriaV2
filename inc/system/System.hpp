#ifndef __SYSTEM__
#define __SYSTEM__

#include <string>

/**
 * Purpose:
 * 	This abstract class acts as a facade for all systems to allow each system
 * 	to be disabled with a config setting.
 */
class System
{
public:
	System(std::string const& systemConfigItem);

	virtual ~System();
	void Update();

private:
	virtual void Update_() = 0;

	bool IsSystemEnabled_();

	bool IsSystemLogged_();

	std::string const m_systemConfigItem;
	std::string const m_kLogSystemTime;
};

#endif