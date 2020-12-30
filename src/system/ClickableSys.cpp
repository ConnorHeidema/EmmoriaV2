#include "system/ClickableSys.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/LocationComp.hpp"

#include "util/MouseUtils.hpp"

#include <entt/entt.hpp>

#include <iostream>
#include <SFML/Window/Mouse.hpp>

ClickableSys::ClickableSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_bLeftClicked(false)
	, m_bRightClicked(false)
{ }

void ClickableSys::Update_()
{
	m_rReg.view<ClickableComp, SizeComp, PositionComp>()
		.each([&](auto entity, auto& clickableComp, auto& sizeComp, auto& positionComp)
	{
		int x = 0;
		int y = 0;
		m_rReg.view<LocationComp>()
			.each([&](auto entity, auto& locationComp)
		{
			x = ApplicationParameters::k_rightOfScreen * locationComp.xLocation;
			y = ApplicationParameters::k_bottomOfScreen * locationComp.yLocation;
		});
		clickableComp.m_x = (double)sf::Mouse::getPosition().x / (double)ApplicationParameters::k_widthAdjustment;
		clickableComp.m_y = (double)sf::Mouse::getPosition().y / (double)ApplicationParameters::k_heightAdjustment;

		if (MouseUtils::IsCollisionDetected_(
				positionComp.m_position.x - sizeComp.m_size.width/2,
				positionComp.m_position.y - sizeComp.m_size.height/2,
				sizeComp.m_size.width,
				sizeComp.m_size.height,
				sf::Mouse::getPosition().x + x,
				sf::Mouse::getPosition().y + y))
		{
			clickableComp.m_bLeftDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			clickableComp.m_bRightDown = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		}
	});
	CheckClick_(static_cast<int>(sf::Mouse::Left));
	CheckClick_(static_cast<int>(sf::Mouse::Right));
}

void ClickableSys::CheckClick_(int clickInt)
{
	sf::Mouse::Button click = static_cast<sf::Mouse::Button>(clickInt);
	bool& buttonClicked = ((click == sf::Mouse::Left ? m_bLeftClicked : m_bRightClicked));

	if (buttonClicked && sf::Mouse::isButtonPressed(click))
	{
		m_rReg.view<ClickableComp, SizeComp, PositionComp>()
			.each([&](auto entity, auto& clickableComp, auto& sizeComp, auto& positionComp)
		{
			bool& compClicked = (click == sf::Mouse::Left ? clickableComp.m_bLeftClicked : clickableComp.m_bRightClicked);
			compClicked = false;
		});
		return;
	}

	if (!sf::Mouse::isButtonPressed(click))
	{
		m_rReg.view<ClickableComp, SizeComp, PositionComp>()
			.each([&](auto entity, auto& clickableComp, auto& sizeComp, auto& positionComp)
		{
			bool& compClicked = (click == sf::Mouse::Left ?
				clickableComp.m_bLeftClicked :
				clickableComp.m_bRightClicked);
			compClicked = false;
		});
		buttonClicked = false;
		return;
	}

	buttonClicked = true;

	int x = 0;
	int y = 0;
	m_rReg.view<LocationComp>()
		.each([&](auto entity, auto& locationComp)
	{
		x = ApplicationParameters::k_rightOfScreen * locationComp.xLocation;
		y = ApplicationParameters::k_bottomOfScreen * locationComp.yLocation;
	});
	m_rReg.view<ClickableComp, SizeComp, PositionComp>()
		.each([&](auto entity, auto& clickableComp, auto& sizeComp, auto& positionComp)
	{
		if (sf::Mouse::isButtonPressed(click) &&
			MouseUtils::IsCollisionDetected_(
				positionComp.m_position.x - sizeComp.m_size.width/2,
				positionComp.m_position.y - sizeComp.m_size.height/2,
				sizeComp.m_size.width,
				sizeComp.m_size.height,
				sf::Mouse::getPosition().x + x,
				sf::Mouse::getPosition().y + y))
		{
			bool& compClicked = (click == sf::Mouse::Left ? clickableComp.m_bLeftClicked : clickableComp.m_bRightClicked);
			compClicked = true;
		}
	});
}