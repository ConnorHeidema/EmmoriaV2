#include "system/ButtonSys.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/MovieComp.hpp"
#include "component/RenderableTextComp.hpp"
#include "component/PositionComp.hpp"

#include "util/Mediamap.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

ButtonSys::ButtonSys(entt::registry& rReg)
	: m_rReg(rReg)
	, m_MovieDelayFrame(0)
	, m_MovieDelayFrameMax(24)
{ }

void ButtonSys::Update()
{
	m_rReg.view<ClickableComp>(entt::exclude<RenderableTextComp>)
		.each([&](auto entity, auto &clickableComp2)
	{
		if (clickableComp2.leftClicked && m_MovieDelayFrame == 0)
		{
			auto startMovie = m_rReg.create();
			auto& movieComp = m_rReg.emplace<MovieComp>(startMovie);
			movieComp.m_currentMedia = Media_t::NEW_GAME_SELECTED;
			m_MovieDelayFrame++;
		}
		if (m_MovieDelayFrame > 0)
		{
			m_MovieDelayFrame++;
		}
	});

	if (m_MovieDelayFrame == m_MovieDelayFrameMax)
	{
		m_MovieDelayFrame = 0;
		m_rReg.view<PositionComp>(entt::exclude<MovieComp>).each([&](auto entity, auto& posComp)
		{
			m_rReg.destroy(entity);
		});
	}
}