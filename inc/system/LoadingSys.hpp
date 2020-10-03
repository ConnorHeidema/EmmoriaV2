#ifndef __LOADING_SYS__
#define __LOADING_SYS__

#include "system/System.hpp"


#include <entt/entt.hpp>

class LoadingSys
	: public System
{
public:
	LoadingSys(std::string systemConfigItem, entt::registry& reg);
private:
	void Update_() override;

	entt::registry& m_rReg;
};

#endif