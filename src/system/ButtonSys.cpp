#include "system/ButtonSys.hpp"

#include "component/tag/ButtonComp.hpp"
#include "component/tag/PersistentComp.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/MovieComp.hpp"

#include "util/Mediamap.hpp"

#include <SFML/Graphics.hpp>

ButtonSys::ButtonSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void ButtonSys::Update()
{
	Media_t movieToPlay = Media_t::NONE;
	m_rReg.view<ButtonComp, TextComp, ClickableComp>().each([&](
		auto entity,
		auto& textComp,
		auto& clickableComp)
	{
		if (clickableComp.m_bLeftClicked)
		{
			if (textComp.m_text == "New Game")
			{
				movieToPlay = Media_t::NEW_GAME_SELECTED;
			}
		}
	});
	if (movieToPlay != Media_t::NONE)
	{
		auto movie = m_rReg.create();
		m_rReg.emplace<PersistentComp>(movie);
		auto& media = m_rReg.emplace<MovieComp>(movie);
		media.m_currentMedia = movieToPlay;
	}
}