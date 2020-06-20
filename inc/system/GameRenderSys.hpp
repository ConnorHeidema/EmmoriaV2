#ifndef __GAME_RENDER_SYS__
#define __GAME_RENDER_SYS__

#include "system/IGraphicsSystem.hpp"

class GameRenderSys
	: public IGraphicsSystem
{
public:
	GameRenderSys();

	void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow) override;
};

#endif