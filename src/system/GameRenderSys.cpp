#include "system/GameRenderSys.hpp"

#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"

#include "util/Mediamap.hpp"

GameRenderSys::GameRenderSys()
{ }

void GameRenderSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	reg.view<PositionComp, RenderableComp>().each([pRenderWindow](auto entity, auto &posComp)
	{
		// dummy data for now
		auto a = sf::RectangleShape(sf::Vector2f(20,20));
		a.setFillColor(sf::Color::Green);
		a.setPosition(posComp.position.x, posComp.position.y);
		pRenderWindow->draw(a);
	});
}