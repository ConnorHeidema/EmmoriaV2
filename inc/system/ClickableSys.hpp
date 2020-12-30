#ifndef __CLICKABLE_SYS__
#define __CLICKABLE_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

class ClickableSys
	: public System
{
public:
	ClickableSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	void CheckClick_(int clickInt);

	entt::registry& m_rReg;

	bool m_bLeftClicked;
	bool m_bRightClicked;
};

#endif