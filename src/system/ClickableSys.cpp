#include "system/ClickableSys.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/PositionComp.hpp"

#include "util/MouseUtils.hpp"

#include <iostream>

ClickableSys::ClickableSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_bLeftClicked(false)
	, m_bRightClicked(false)
{ }

void ClickableSys::Update()
{
	CheckClick_(sf::Mouse::Left);
	CheckClick_(sf::Mouse::Right);
}

void ClickableSys::CheckClick_(sf::Mouse::Button click)
{
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
			bool& compClicked = (click == sf::Mouse::Left ? clickableComp.m_bLeftClicked : clickableComp.m_bRightClicked);
			compClicked = false;
		});
		buttonClicked = false;
		return;
	}

	buttonClicked = true;
	m_rReg.view<ClickableComp, SizeComp, PositionComp>()
		.each([&](auto entity, auto& clickableComp, auto& sizeComp, auto& positionComp)
	{
		if (sf::Mouse::isButtonPressed(click) &&
			MouseUtils::IsCollisionDetected_(
				positionComp.m_position.x - sizeComp.m_size.width/2,
				positionComp.m_position.y - sizeComp.m_size.height/2,
				sizeComp.m_size.width,
				sizeComp.m_size.height,
				sf::Mouse::getPosition().x,
				sf::Mouse::getPosition().y))
		{
			bool& compClicked = (click == sf::Mouse::Left ? clickableComp.m_bLeftClicked : clickableComp.m_bRightClicked);
			std::cout << "Clicked on clickable object" << std::endl;
			compClicked = true;
		}
	});
}