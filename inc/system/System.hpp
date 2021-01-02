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
	System(std::string const& systemName);

	virtual ~System();
	void SetRunning(bool const bRunning);
	void Update();
	std::string GetName();
private:
	virtual void Update_() = 0;

	bool IsSystemEnabled_();

	bool IsSystemLogged_();

	std::string const m_systemName;
	std::string const m_kLogSystemTime;
	bool m_bEnabled;
};

#endif