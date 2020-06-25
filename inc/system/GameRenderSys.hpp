#ifndef __GAME_RENDER_SYS__
#define __GAME_RENDER_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

class GameRenderSys
	: public ISystem
{
public:
	GameRenderSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow);

	void Update() override;

private:
	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
};

#endif