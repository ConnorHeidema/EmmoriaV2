#ifndef __GAME_RENDER_SYS__
#define __GAME_RENDER_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

class GameRenderSys
	: public System
{
public:
	GameRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow);

private:
	void Update_() override;
	void RenderHealth_();

	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
};

#endif