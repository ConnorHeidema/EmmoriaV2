#include "system/ButtonSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/ButtonComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/LoadComp.hpp"
#include "component/functional/MovieComp.hpp"
#include "entity/EntityLoaderFactory.hpp"
#include "util/Mediamap.hpp"

#include "util/ApplicationParameters.hpp"

#include <entt/entt.hpp>

#include <sstream>
#include <fstream>

ButtonSys::ButtonSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void ButtonSys::Update_()
{
	Media_t movieToPlay = Media_t::NONE;

	std::string buttonPressed = "";
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
			else if (buttonComp.m_action == "LoadGame")
			{
				buttonPressed = "LoadGame";
			}
			else if (buttonComp.m_action == "BackButton")
			{
				auto reboot = m_rReg.create();
				m_rReg.emplace<RebootComp>(reboot);
			}
			else if (buttonComp.m_action == "LoadFile1")
			{
				m_rReg.clear();
				auto entity = m_rReg.create();
				m_rReg.emplace<LoadComp>(entity).m_filePath = "Files/0";
			}
			else if (buttonComp.m_action == "LoadFile2")
			{
				m_rReg.clear();
				auto entity = m_rReg.create();
				m_rReg.emplace<LoadComp>(entity).m_filePath = "Files/0";
			}
			else if (buttonComp.m_action == "LoadFile3")
			{
				m_rReg.clear();
				auto entity = m_rReg.create();
				m_rReg.emplace<LoadComp>(entity).m_filePath = "Files/0";
			}
		}
	});

	if (buttonPressed == "LoadGame")
	{
		bool fileExists = false;
		std::ifstream f(ApplicationParameters::k_dataPath + "Files/0");
		std::ifstream f2(ApplicationParameters::k_dataPath + "Files/1");
		std::ifstream f3(ApplicationParameters::k_dataPath + "Files/2");
		if (!f.good() && !f2.good() && !f3.good())
		{
			return;
		}
		m_rReg.view<ButtonComp, ClickableComp>().each([&](
			auto entity,
			auto& buttonComp,
			auto& clickableComp)
		{
			m_rReg.destroy(entity);
		});
    	if (f.good())
		{
			std::istringstream s("LoadFile1 60 70 4 Load File 1 \\");
			auto entity = m_rReg.create();
			EntityLoaderFactory::LoadButton(m_rReg, entity, s);
		}
    	if (f2.good())
		{
			std::istringstream s("LoadFile2 60 80 4 Load File 2 \\");
			auto entity = m_rReg.create();
			EntityLoaderFactory::LoadButton(m_rReg, entity, s);
		}
    	if (f3.good())
		{
			std::istringstream s("LoadFile3 60 90 4 Load File 3 \\");
			auto entity = m_rReg.create();
			EntityLoaderFactory::LoadButton(m_rReg, entity, s);
		}
		f.close();
		f2.close();
		f3.close();
		std::istringstream s("BackButton 10 5 4 Back \\");
		auto entity = m_rReg.create();
		EntityLoaderFactory::LoadButton(m_rReg, entity, s);
	}

	if (movieToPlay != Media_t::NONE)
	{
		auto movie = m_rReg.create();
		m_rReg.emplace<PersistentComp>(movie);
		auto& media = m_rReg.emplace<MovieComp>(movie);
		media.m_currentMedia = movieToPlay;
	}
}