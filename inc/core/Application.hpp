#ifndef __APPLICATION__
#define __APPLICATION__

#include "util/Size.hpp"

#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
#include "system/MovieRenderSys.hpp"
#include "system/GameRenderSys.hpp"
#include "system/LoadingSys.hpp"
#include "system/ClickableSys.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include <memory>

class Application
{
public:
	Application();
	bool Start();

private:
	void Initialize_();
	void RunLoop_();
	void CheckForEvents_();

	MovementSys m_movementSys;
	PrintMovementSys m_printMovementSys;
	MovieRenderSys m_movieRenderSys;
	GameRenderSys m_gameRenderSys;
	LoadingSys m_loadingSys;
	ClickableSys m_clickableSys;

	entt::registry m_reg;

	std::shared_ptr<sf::RenderWindow> m_renderWindow;
};

#endif