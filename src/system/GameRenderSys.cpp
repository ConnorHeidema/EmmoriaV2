#include "system/GameRenderSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapPtrComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/DialogComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/stats/MaxHealthComp.hpp"

#include "util/Mediamap.hpp"
#include "util/ApplicationParameters.hpp"
#include "util/Helper.hpp"
#include "util/TextureContainer.hpp"
#include "util/FontContainer.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <math.h>

#include <iostream>

GameRenderSys::GameRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

void GameRenderSys::Update_()
{
	ResetRenderState_();
	RenderTileMapPieces_();
	RenderRotatableSprites_();
	RenderBasicSprites_();
	RenderText_();
	RenderHealth_();
	RenderDialog_();
}

void GameRenderSys::ResetRenderState_()
{
	m_rReg.view<RenderableComp>().each([&](
	auto entity,
	auto& renderableComp)
	{
		renderableComp.m_bRendered = false;
	});
}


void GameRenderSys::RenderTileMapPieces_()
{
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
}

void GameRenderSys::RenderRotatableSprites_()
{
	m_rReg.view<RenderableComp, PositionComp, SizeComp, SpriteComp, RotationComp>().each([&](
		auto entity,
		auto& renderableComp,
		auto& positionComp,
		auto& sizeComp,
		auto& spriteComp,
		auto& rotationComp)
	{
		if (renderableComp.m_bRendered == false)
		{
			auto genericSprite = sf::RectangleShape(sf::Vector2f(sizeComp.m_size.width, sizeComp.m_size.height));
			sf::Texture texture;
			texture = *TextureContainer::GetTexture(spriteComp.m_filePath); // this should be stored somehow
			genericSprite.setTexture(&texture);
			sf::Transform transform;
        	transform.rotate(
				rotationComp.m_angle * 90 / tan(1) + 90,
				sf::Vector2f(
					Helper::Mod((int)positionComp.m_position.x, ApplicationParameters::k_rightOfScreen),
					Helper::Mod((int)positionComp.m_position.y, ApplicationParameters::k_bottomOfScreen)));

			genericSprite.setPosition(
				Helper::Mod((int)positionComp.m_position.x, ApplicationParameters::k_rightOfScreen) - (int)sizeComp.m_size.width/2,
				Helper::Mod((int)positionComp.m_position.y, ApplicationParameters::k_bottomOfScreen) - (int)sizeComp.m_size.height/2);

			genericSprite.setTextureRect(
				sf::IntRect(
					spriteComp.m_spriteIndex * spriteComp.m_width,
					0,
					spriteComp.m_width,
					spriteComp.m_height));


			m_rRenderWindow.draw(genericSprite, transform);
			renderableComp.m_bRendered = true;
		}
	});
}


void GameRenderSys::RenderBasicSprites_()
{
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
			texture = *TextureContainer::GetTexture(spriteComp.m_filePath); // this should be stored somehow
			genericSprite.setTexture(&texture);
			genericSprite.setPosition(
				Helper::Mod((int)positionComp.m_position.x, ApplicationParameters::k_rightOfScreen) - (int)sizeComp.m_size.width/2,
				Helper::Mod((int)positionComp.m_position.y, ApplicationParameters::k_bottomOfScreen) - (int)sizeComp.m_size.height/2);
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
}


void GameRenderSys::RenderText_()
{
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
			rectShape.setFillColor(sf::Color(0,255,0,150));
			m_rRenderWindow.draw(rectShape);

			sf::Text text;
			sf::Font font;
			font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
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
}

void GameRenderSys::RenderHealth_()
{
	m_rReg.view<PlayerComp, HealthComp, MaxHealthComp>().each([&](
		auto entity,
		auto& healthComp,
		auto& maxHealthComp)
	{
		sf::Text text;
		sf::Font font;
		font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		text.setString(std::string("Health: ") + std::to_string(healthComp.m_health));
		text.setPosition(sf::Vector2f(50, 920));
		m_rRenderWindow.draw(text);

		RenderHealthBar_(text.getLocalBounds().width, 50, 920, float(healthComp.m_health) / float(maxHealthComp.m_maxHealth));
	});
	// all enemies should have health above head
	m_rReg.view<HealthComp, SizeComp, PositionComp, MaxHealthComp>().each([&](
		auto entity,
		auto& healthComp,
		auto& sizeComp,
		auto& positionComp,
		auto& maxHealthComp)
	{
		if (!m_rReg.has<PlayerComp>(entity))
		{
			RenderHealthBar_(
				float(sizeComp.m_size.width),
				Helper::Mod(int(positionComp.m_position.x - float(sizeComp.m_size.width/2)), ApplicationParameters::k_rightOfScreen),
				Helper::Mod(int(positionComp.m_position.y - sizeComp.m_size.height/2 - 10), ApplicationParameters::k_bottomOfScreen),
				float(healthComp.m_health) / float(maxHealthComp.m_maxHealth));
		}
	});
}

void GameRenderSys::RenderDialog_()
{	m_rReg.view<RenderableComp, DialogComp, ClickableComp, PositionComp, SizeComp>().each([&](
		auto entity,
		auto& renderableComp,
		auto& dialogComp,
		auto& clickableComp,
		auto& positionComp,
		auto& sizeComp)
	{
		if (renderableComp.m_bRendered == false)
		{
			sf::RectangleShape rect(sf::Vector2f(1714.f, 174.f));
			rect.setFillColor(sf::Color(0,0,255,150)); // blue
			rect.setOutlineColor(sf::Color(0,255,0,150)); // green
			rect.setOutlineThickness(3.f);
			rect.setPosition(sf::Vector2f(100.f, 903.f));
			m_rRenderWindow.draw(rect);

			sf::RectangleShape portraitRect(sf::Vector2f(280, 134.f));
			portraitRect.setPosition(sf::Vector2f(110.f, 923.f));

			sf::Texture texture;
			texture = *TextureContainer::GetTexture(std::string("sprite/portrait/") + std::string(dialogComp.m_portrait) + std::string(".png"));
			portraitRect.setTexture(&texture);
			portraitRect.setTextureRect(
				sf::IntRect(
					0,
					0,
					100,
					100));
			portraitRect.setOutlineColor(sf::Color(0,255,255,150));
			portraitRect.setOutlineThickness(3.f);
			m_rRenderWindow.draw(portraitRect);


			sf::Font font;
			font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
			std::string firstThingToWrite = dialogComp.m_dialogList.front();
			if (dialogComp.m_dialogList.size() == 2 ||dialogComp.m_dialogList.size() == 3)
			{
				std::string nextThingToWrite = *std::next(dialogComp.m_dialogList.begin());
				firstThingToWrite += "\n" + nextThingToWrite;
			}
			if (dialogComp.m_dialogList.size() == 3)
			{
				std::string nextThingToWrite = *std::next(std::next(dialogComp.m_dialogList.begin()));
				firstThingToWrite += "\n" + nextThingToWrite;
			}
			sf::Text text(firstThingToWrite, font, 50);
			text.setPosition(400.f, 903.f);
			m_rRenderWindow.draw(text);

			renderableComp.m_bRendered = true;
		}
	});
}

void GameRenderSys::RenderHealthBar_(
	float const& spriteWidth,
	float const& xPosition,
	float const& yPosition,
	float const& healthRatio)
{
	float const amountAboveSprite = 15.f;
	float const heightOfBar = 10.f;
	sf::RectangleShape remainingHealth(sf::Vector2f(healthRatio * spriteWidth, heightOfBar));
	remainingHealth.setPosition(sf::Vector2f(xPosition, yPosition - amountAboveSprite));
	remainingHealth.setFillColor(sf::Color::Green);
	m_rRenderWindow.draw(remainingHealth);
}