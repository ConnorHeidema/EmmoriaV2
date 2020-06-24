#include "system/GameRenderSys.hpp"

#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/SpriteComp.hpp"
#include "component/SizeComp.hpp"
#include "component/PositionComp.hpp"

#include "util/Mediamap.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

GameRenderSys::GameRenderSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

void GameRenderSys::Update()
{
	m_rReg.view<PositionComp, SizeComp, SpriteComp>().each([&](
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
		m_rRenderWindow.draw(genericSprite);
	});

	m_rReg.view<PositionComp, SizeComp, RenderableComp>().each([&](
		auto entity,
		auto &posComp,
		auto &sizeComp)
	{
		sf::RectangleShape rectShape(sf::Vector2f(sizeComp.size.width,sizeComp.size.height));
		rectShape.setPosition(sf::Vector2f(posComp.position.x, posComp.position.y));
		rectShape.setFillColor(sf::Color::Green);
		m_rRenderWindow.draw(rectShape);
	});

	// reg.view<PositionComp, RenderableComp>().each([m_pRenderWindow](auto entity, auto &posComp)
	// {
	// 	// dummy data for now
	// 	auto a = sf::RectangleShape(sf::Vector2f(20, 20));
	// 	a.setFillColor(sf::Color::Green);
	// 	a.setPosition(posComp.position.x, posComp.position.y);
	// 	m_pRenderWindow->draw(a);
	// });
}