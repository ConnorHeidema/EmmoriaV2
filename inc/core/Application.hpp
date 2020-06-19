#ifndef __APPLICATION__
#define __APPLICATION__

#include "util/Size.hpp"

#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
#include "system/RenderSystem.hpp"

#include <sfeMovie/Movie.hpp>
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class Application
{
public:
	Application();
	bool Start();

private:
	void RunLoop_(sf::RenderWindow& gameWindow);
	void CheckForEvents_(sf::RenderWindow& gameWindow);

	MovementSys m_movementSys;
	PrintMovementSys m_printMovementSys;
	RenderSystem m_renderSystem;

	entt::registry m_reg;
};

#endif