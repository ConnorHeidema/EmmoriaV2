#include "system/GameRenderSys.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapPtrComp.hpp"
#include "component/functional/HealthComp.hpp"

#include "util/Mediamap.hpp"
#include "util/ApplicationParameters.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

GameRenderSys::GameRenderSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

void GameRenderSys::Update()
{
	m_rReg.view<RenderableComp>().each([&](
	auto entity,
	auto& renderableComp)
	{
		renderableComp.m_bRendered = false;
	});

	m_rReg.view<TileMapPtrComp, RenderableComp>().each([&](
		auto entity,
		auto& tileMapPtrComp,
		auto& renderableComp)
	{
		if (tileMapPtrComp.m_pTileMap != nullptr)
		{
			m_rRenderWindow.draw(*tileMapPtrComp.m_pTileMap);
			renderableComp.m_bRendered = true;
		}
	});

	m_rReg.view<RenderableComp, PositionComp, SizeComp, SpriteComp>().each([&](
		auto entity,
		auto& renderableComp,
		auto& positionComp,
		auto& sizeComp,
		auto& spriteComp)
	{
		if (renderableComp.m_bRendered == false)
		{
			auto genericSprite = sf::RectangleShape(sf::Vector2f(sizeComp.m_size.width, sizeComp.m_size.height));
			sf::Texture texture;
			texture.loadFromFile(spriteComp.m_filePath); // this should be stored somehow
			genericSprite.setTexture(&texture);
			genericSprite.setPosition(
				(positionComp.m_position.x % ApplicationParameters::k_rightOfScreen) - (int)sizeComp.m_size.width/2,
				(positionComp.m_position.y % ApplicationParameters::k_bottomOfScreen) - (int)sizeComp.m_size.height/2);

			genericSprite.setTextureRect(
				sf::IntRect(
					spriteComp.m_spriteIndex * spriteComp.m_width,
					0,
					spriteComp.m_width,
					spriteComp.m_height));

			m_rRenderWindow.draw(genericSprite);
			renderableComp.m_bRendered = true;
		}
	});

	m_rReg.view<RenderableComp, PositionComp, SizeComp, TextComp>().each([&](
		auto entity,
		auto& renderableComp,
		auto& positionComp,
		auto& sizeComp,
		auto& textComp)
	{
		if (renderableComp.m_bRendered == false)
		{
			sf::RectangleShape rectShape(sf::Vector2f(sizeComp.m_size.width,sizeComp.m_size.height));
			rectShape.setPosition(
				sf::Vector2f(
					positionComp.m_position.x - sizeComp.m_size.width/2,
					positionComp.m_position.y - sizeComp.m_size.height/2));
			rectShape.setFillColor(sf::Color::Green);
			m_rRenderWindow.draw(rectShape);

			sf::Text text;
			sf::Font font;
			font.loadFromFile(ApplicationParameters::k_fontPath);
			text.setFont(font);
			text.setCharacterSize(sizeComp.m_size.height*ApplicationParameters::k_textFactor);
			text.setString(textComp.m_text);
			text.setPosition(
				sf::Vector2f(
					positionComp.m_position.x - sizeComp.m_size.width/2,
					positionComp.m_position.y - sizeComp.m_size.height/2));
			m_rRenderWindow.draw(text);
			renderableComp.m_bRendered = true;
		}
	});
	RenderHealth_();
}

void GameRenderSys::RenderHealth_()
{
	m_rReg.view<HealthComp>().each([&](
		auto entity,
		auto& healthComp)
	{
		sf::Text text;
		sf::Font font;
		font.loadFromFile(ApplicationParameters::k_fontPath);
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		text.setString(std::string("Health: ") + std::to_string(healthComp.m_health));
		text.setPosition(sf::Vector2f(50, 1000));
		m_rRenderWindow.draw(text);
	});
}