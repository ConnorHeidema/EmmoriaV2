#include "system/ClickableSys.hpp"

#include "component/PositionComp.hpp"
#include "component/ClickableComp.hpp"
#include "component/SizeComp.hpp"
#include "component/MovieComp.hpp"
#include "component/RenderableTextComp.hpp"

#include "util/Mediamap.hpp"
#include "util/MouseUtils.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

ClickableSys::ClickableSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_MovieDelayFrame(0)
	, m_MovieDelayFrameMax(24)
{

}

void ClickableSys::Update()
{
	m_xMousePosition = sf::Mouse::getPosition().x;
	m_yMousePosition = sf::Mouse::getPosition().y;

	m_rReg.view<PositionComp, SizeComp, ClickableComp>(entt::exclude<RenderableTextComp>)
		.each([&](auto entity, auto &posComp, auto &sizeComp)
	{
		if (MouseUtils::IsCollisionDetected_(
			posComp.position.x,
			posComp.position.y,
			sizeComp.size.width,
			sizeComp.size.height,
			m_xMousePosition,
			m_yMousePosition))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MovieDelayFrame == 0)
			{
				auto startMovie = m_rReg.create();
				auto& movieComp = m_rReg.emplace<MovieComp>(startMovie);
				movieComp.m_currentMedia = Media_t::NEW_GAME_SELECTED;
				m_MovieDelayFrame++;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				std::cout << "Right clicked" << std::endl;
			}
			std::cout << "Mouse position at : (" +
				std::to_string(sf::Mouse::getPosition().x) + ", " +
				std::to_string(sf::Mouse::getPosition().y) + ")" << std::endl;

			if (m_MovieDelayFrame > 0)
			{
				m_MovieDelayFrame++;
			}
		}
	});

	if (m_MovieDelayFrame == m_MovieDelayFrameMax)
	{
		m_MovieDelayFrame = 0;
		m_rReg.view<PositionComp>(entt::exclude<MovieComp>).each([&](auto entity, auto &posComp)
		{
			m_rReg.destroy(entity);
		});
	}
}