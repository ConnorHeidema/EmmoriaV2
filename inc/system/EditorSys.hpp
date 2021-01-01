#ifndef __EDITOR_SYS__
#define __EDITOR_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

namespace sf { class RenderWindow; }

class EditorSys
	: public System
{
public:
	EditorSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow);

private:
	void Update_() override;

	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
};

#endif