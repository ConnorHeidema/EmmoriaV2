#ifndef __CLICKABLE_SYS__
#define __CLICKABLE_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>
#include <SFML/Window.hpp>

class ClickableSys
	: public System
{
public:
	ClickableSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	void CheckClick_(sf::Mouse::Button click);

	entt::registry& m_rReg;

	bool m_bLeftClicked;
	bool m_bRightClicked;
};

#endif