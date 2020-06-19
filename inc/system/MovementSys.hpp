#ifndef __MOVEMENT_SYS__
#define __MOVEMENT_SYS__

#include "system/ISystem.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"

#include <SFML/Graphics.hpp>

class MovementSys
	: public ISystem
{
public:
	void Update(entt::registry& reg) override
	{
	reg.view<PlayerComp, PositionComp>().each([](auto entity, auto &posComp) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			posComp.position.x -= 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			posComp.position.y -= 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			posComp.position.x += 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			posComp.position.y += 3;
		}
	 });
	}
};

#endif