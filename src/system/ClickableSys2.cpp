#include "system/ClickableSys.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/SizeComp.hpp"
#include "component/PositionComp.hpp"

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
		return;
	}
	else if (buttonClicked && !sf::Mouse::isButtonPressed(click))
	{
		buttonClicked = false;
	}
	m_rReg.view<ClickableComp, SizeComp, PositionComp>()
		.each([&](auto entity, auto &clickableComp2, auto& sizeComp, auto& posComp)
	{
		if (sf::Mouse::isButtonPressed(click) &&
			MouseUtils::IsCollisionDetected_(
				posComp.position.x,
				posComp.position.y,
				sizeComp.size.width,
				sizeComp.size.height,
				sf::Mouse::getPosition().x,
				sf::Mouse::getPosition().y))
		{
			bool& compClicked = (click == sf::Mouse::Left ? clickableComp2.leftClicked : clickableComp2.rightClicked);
			std::cout << "Clicked on clickable object" << std::endl;
			compClicked = true;
			buttonClicked = true;
		}
	});
}