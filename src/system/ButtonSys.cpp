#include "system/ButtonSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/ButtonComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/MovieComp.hpp"

#include "util/Mediamap.hpp"

ButtonSys::ButtonSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void ButtonSys::Update_()
{
	Media_t movieToPlay = Media_t::NONE;
	m_rReg.view<ButtonComp, ClickableComp>().each([&](
		auto entity,
		auto& buttonComp,
		auto& clickableComp)
	{
		if (clickableComp.m_bLeftClicked)
		{
			if (buttonComp.m_action == "NewGame")
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