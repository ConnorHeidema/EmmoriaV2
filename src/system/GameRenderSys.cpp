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
#include "component/functional/SoundComp.hpp"

#include "util/Mediamap.hpp"
#include "util/ApplicationParameters.hpp"
#include "util/Helper.hpp"
#include "util/TextureContainer.hpp"
#include "util/FontContainer.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Audio/Music.hpp>

#include <math.h>

GameRenderSys::GameRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

void GameRenderSys::Update_()
{
	ResetRenderState_();
	RenderTileMapPieces_();
	RenderBasicSprites_(); // slowest part of program in this function
	RenderText_();
	RenderHealth_();
	RenderDialog_();
}

void GameRenderSys::ResetRenderState_()
{
	m_rReg.view<RenderableComp>().each([&](auto& renderableComp)
	{
		renderableComp.m_bRendered = false;
	});
}


void GameRenderSys::RenderTileMapPieces_()
{
	m_rReg.view<TileMapPtrComp, RenderableComp>().each([&]
		(auto& tileMapPtrComp,
		auto& renderableComp)
	{
		if (tileMapPtrComp.m_pTileMap != nullptr)
		{
			m_rRenderWindow.draw(*tileMapPtrComp.m_pTileMap);
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
			auto& pos = positionComp.m_position;
			auto& size = sizeComp.m_size;
			auto const k_tan1 = tanf(1);
			auto genericSprite = sf::RectangleShape(sf::Vector2f((float)size.width, (float)size.height));
			genericSprite.setTexture(&(*TextureContainer::GetTexture(spriteComp.m_filePath)));

			genericSprite.setPosition(
				(float)Helper::Mod((int)pos.x, ApplicationParameters::k_rightOfScreen) - (int)size.width/2.f,
				(float)Helper::Mod((int)pos.y, ApplicationParameters::k_bottomOfScreen) - (int)size.height/2.f);

			genericSprite.setTextureRect(
				sf::IntRect(
					spriteComp.m_spriteIndex * spriteComp.m_width,
					0,
					spriteComp.m_width,
					spriteComp.m_height));
			genericSprite.setOutlineThickness(-2);
			genericSprite.setOutlineColor(sf::Color::Red);
			if (m_rReg.has<RotationComp>(entity))
			{
				auto& angle = m_rReg.get<RotationComp>(entity).m_angle;
				sf::Transform transform;
				transform.rotate(
					float((angle * 90.L / k_tan1) + 90.L),
					sf::Vector2f(
						(float)Helper::Mod((int)pos.x, ApplicationParameters::k_rightOfScreen),
						(float)Helper::Mod((int)pos.y, ApplicationParameters::k_bottomOfScreen)));
				m_rRenderWindow.draw(genericSprite, transform);
			}
			else
			{
				m_rRenderWindow.draw(genericSprite);
			}
			renderableComp.m_bRendered = true;
		}
	});
}

void GameRenderSys::RenderText_()
{
	m_rReg.view<RenderableComp, PositionComp, SizeComp, TextComp>().each([&](
		auto& renderableComp,
		auto& positionComp,
		auto& sizeComp,
		auto& textComp)
	{
		if (renderableComp.m_bRendered == false)
		{
			sf::RectangleShape rectShape(sf::Vector2f((float)sizeComp.m_size.width, (float)sizeComp.m_size.height));
			rectShape.setPosition(
				sf::Vector2f(
					(float)positionComp.m_position.x - sizeComp.m_size.width/2.f,
					(float)positionComp.m_position.y - sizeComp.m_size.height/2.f));
			rectShape.setFillColor(sf::Color(0,255,0,150));
			m_rRenderWindow.draw(rectShape);

			sf::Text text;
			text.setFont(*FontContainer::GetFont(ApplicationParameters::k_fontPath));
			text.setCharacterSize(static_cast<unsigned int>(float(sizeComp.m_size.height)*ApplicationParameters::k_textFactor));
			text.setString(textComp.m_text);
			text.setPosition(
				sf::Vector2f(
					(float)positionComp.m_position.x - sizeComp.m_size.width/2,
					(float)positionComp.m_position.y - sizeComp.m_size.height/2));
			m_rRenderWindow.draw(text);
			renderableComp.m_bRendered = true;
		}
	});
}

void GameRenderSys::RenderHealth_()
{
	m_rReg.view<PlayerComp, HealthComp, MaxHealthComp>().each([&](
		auto& healthComp,
		auto& maxHealthComp)
	{
		sf::Text text;
		text.setFont(*FontContainer::GetFont(ApplicationParameters::k_fontPath));
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
				(float)Helper::Mod(int(positionComp.m_position.x - float(sizeComp.m_size.width/2)), ApplicationParameters::k_rightOfScreen),
				(float)Helper::Mod(int(positionComp.m_position.y - sizeComp.m_size.height/2 - 10), ApplicationParameters::k_bottomOfScreen),
				float(healthComp.m_health) / float(maxHealthComp.m_maxHealth));
		}
	});
}

void GameRenderSys::RenderDialog_()
{
	static sf::Text text("", *FontContainer::GetFont(ApplicationParameters::k_fontPath), 50);
	text.setPosition(400.f, 903.f);
	bool b_dialogExists = false;
	m_rReg.view<RenderableComp, DialogComp>().each([&](
		auto& renderableComp,
		auto& dialogComp)
	{
		b_dialogExists = true;
		if (renderableComp.m_bRendered == false)
		{
			sf::Color a;
			sf::RectangleShape rect(sf::Vector2f(1714.f, 174.f));
			rect.setFillColor(sf::Color(0,0,255,150)); // blue
			rect.setOutlineColor(sf::Color(0,255,0,150)); // green
			rect.setOutlineThickness(3.f);
			rect.setPosition(sf::Vector2f(100.f, 903.f));
			m_rRenderWindow.draw(rect);

			sf::RectangleShape portraitRect(sf::Vector2f(280, 134.f));
			portraitRect.setPosition(sf::Vector2f(110.f, 923.f));
			portraitRect.setTexture(
				&(*TextureContainer::GetTexture(
					std::string("sprite/portrait/") + std::string(dialogComp.m_portrait) + std::string(".png"))));
			portraitRect.setTextureRect(
				sf::IntRect(
					0,
					0,
					100,
					100));
			portraitRect.setOutlineColor(sf::Color(0,255,255,150));
			portraitRect.setOutlineThickness(3.f);
			m_rRenderWindow.draw(portraitRect);
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
			if (text.getString().getSize() != firstThingToWrite.size())
			{
				auto entity = m_rReg.create();
				m_rReg.emplace<SoundComp>(entity).m_sound = "dialog.wav";
				text.setString(firstThingToWrite.substr(0, text.getString().getSize() + 1));
			}
			m_rRenderWindow.draw(text);

			renderableComp.m_bRendered = true;
		}
	});
	if (!b_dialogExists)
	{
		text.setString("");
	}
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
