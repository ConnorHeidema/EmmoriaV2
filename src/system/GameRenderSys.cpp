#include "system/GameRenderSys.hpp"

#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/SpriteComp.hpp"
#include "component/SizeComp.hpp"
#include "component/PositionComp.hpp"

#include "util/Mediamap.hpp"

GameRenderSys::GameRenderSys()
{ }

void GameRenderSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	reg.view<PositionComp, SizeComp, SpriteComp>().each([pRenderWindow](
		auto entity,
		auto &posComp,
		auto &sizeComp,
		auto &filePath)
	{
		auto genericSprite = sf::RectangleShape(sf::Vector2f(sizeComp.size.width, sizeComp.size.height));
		sf::Texture texture;
		texture.loadFromFile(filePath.filePath); // this should be stored somehow
		genericSprite.setTexture(&texture);
		genericSprite.setPosition(posComp.position.x, posComp.position.y);
		pRenderWindow->draw(genericSprite);
	});

	reg.view<PositionComp, SizeComp, RenderableComp>().each([pRenderWindow](
		auto entity,
		auto &posComp,
		auto &sizeComp)
	{
		sf::RectangleShape rectShape(sf::Vector2f(sizeComp.size.width,sizeComp.size.height));
		rectShape.setPosition(sf::Vector2f(posComp.position.x, posComp.position.y));
		rectShape.setFillColor(sf::Color::Green);
		pRenderWindow->draw(rectShape);
	});

	// reg.view<PositionComp, RenderableComp>().each([pRenderWindow](auto entity, auto &posComp)
	// {
	// 	// dummy data for now
	// 	auto a = sf::RectangleShape(sf::Vector2f(20, 20));
	// 	a.setFillColor(sf::Color::Green);
	// 	a.setPosition(posComp.position.x, posComp.position.y);
	// 	pRenderWindow->draw(a);
	// });
}