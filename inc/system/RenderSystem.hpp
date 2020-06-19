#ifndef __RENDER_SYS__
#define __RENDER_SYS__

#include "system/IGraphicsSystem.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"

#include <SFML/Graphics.hpp>

class RenderSystem
	: public IGraphicsSystem
{
public:
	void Update(entt::registry& reg, sf::RenderWindow& gameWindow) override
	{

		reg.view<PositionComp, RenderableComp>().each([&gameWindow](auto entity, auto &posComp) {

			auto a = sf::RectangleShape(sf::Vector2f(20,20));
			a.setFillColor(sf::Color::Green);
			a.setPosition(posComp.position.x, posComp.position.y);
			gameWindow.draw(a);
		});
	}
};

#endif