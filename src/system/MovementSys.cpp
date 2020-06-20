#include "system/MovementSys.hpp"

#include "component/MovieComp.hpp"
#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"

void MovementSys::Update(entt::registry& reg)
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
