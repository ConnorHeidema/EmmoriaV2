#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/ISystem.hpp"

#include "util/Size.hpp"
#include "util/Position.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <list>

enum DialogSysState
{
	WAITING,
	CONSUMING,
	PRESENTING
};

class DialogSys
	: public ISystem
{
public:
	DialogSys(entt::registry& reg, sf::RenderWindow& rRenderWindow);
	void Update() override;

private:
	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
};

#endif