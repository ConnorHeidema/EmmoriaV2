#include "system/MovieRenderSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/MovieComp.hpp"
#include "component/functional/LoadComp.hpp"

#include "util/Entitymap.hpp"
#include "util/MediatoEntitymap.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

MovieRenderSys::MovieRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, m_rRenderWindow(rRenderWindow)
	, m_rReg(rReg)
{
	auto movie = m_rReg.create();
	auto& media = m_rReg.emplace<MovieComp>(movie);
	m_rReg.emplace<PersistentComp>(movie);
	media.m_currentMedia = Media_t::INTRO_MOVIE;
	m_lastMedia = Media_t::NONE;
}

void MovieRenderSys::Update_()
{
	bool bRebooted = false;
	m_rReg.view<AnimationRebootComp>().each([&](auto entity)
	{
		auto movie = m_rReg.create();
		auto& media = m_rReg.emplace<MovieComp>(movie);
		m_rReg.emplace<PersistentComp>(movie);
		media.m_currentMedia = Media_t::INTRO_MOVIE;
		m_lastMedia = Media_t::NONE;
		m_rReg.destroy(entity);
	});

	m_rReg.view<MovieComp>().each([&](auto entity, auto& movieComp)
	{
		if (m_lastMedia == Media_t::NONE && movieComp.m_currentMedia != Media_t::NONE)
		{
			std::string const media = Mediamap::m_mediamap.at(movieComp.m_currentMedia);
			auto mediaConfig =
				std::string("Disable") +
				std::string(
					media.substr(media.find_last_of('/') + 1,
					media.find(".") - media.find_last_of('/') - 1));
			if (ConfigItems::m_setConfigItems.find(mediaConfig)
				== ConfigItems::m_setConfigItems.end())
			{
				m_lastMedia = movieComp.m_currentMedia;
				m_movie.openFromFile(media);
				m_movie.play();
			}
		}

		if (m_movie.getStatus() != sfe::Stopped)
		{
			m_movie.update();
			m_rRenderWindow.draw(m_movie);
		}
		else if (movieComp.m_currentMedia != Media_t::NONE)
		{
			m_rReg.destroy(entity);
			auto loadEntity = m_rReg.create();
			auto& load = m_rReg.emplace<LoadComp>(loadEntity);
			load.m_filePath = MediatoEntitymap::m_mediatoEntitymap.at(movieComp.m_currentMedia);
			m_lastMedia = Media_t::NONE;
		}
	});
}
