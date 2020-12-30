#ifndef __BUTTON_SYS__
#define __BUTTON_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>
class ButtonSys
	: public System
{
public:
	ButtonSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	entt::registry& m_rReg;

	entt::entity m_entity;
};

#endif