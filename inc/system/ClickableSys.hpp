#ifndef __CLICKABLE_SYS__
#define __CLICKABLE_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

class ClickableSys
	: public ISystem
{
public:
	ClickableSys(entt::registry& rReg);
	void Update() override;
private:

	void CheckClick_(sf::Mouse::Button click);

	entt::registry& m_rReg;

	bool m_bLeftClicked;
	bool m_bRightClicked;
};

#endif