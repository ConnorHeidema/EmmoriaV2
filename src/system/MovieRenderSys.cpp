#include "system/MovieRenderSys.hpp"

#include "component/functional/MovieComp.hpp"
#include "component/functional/LoadComp.hpp"

#include "util/Entitymap.hpp"
#include "util/MediatoEntitymap.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>


MovieRenderSys::MovieRenderSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rRenderWindow(rRenderWindow)
	, m_rReg(rReg)
{
	auto movie = m_rReg.create();
	auto& media = m_rReg.emplace<MovieComp>(movie);
	media.m_currentMedia = Media_t::INTRO_MOVIE;
	m_lastMedia = Media_t::NONE;
}

void MovieRenderSys::Update()
{
	m_rReg.view<MovieComp>().each([&](auto entity, auto& movieComp)
	{
		if (m_lastMedia == Media_t::NONE && movieComp.m_currentMedia != Media_t::NONE)
		{
			m_lastMedia = movieComp.m_currentMedia;
			m_movie.openFromFile(Mediamap::m_mediamap.at(movieComp.m_currentMedia));
			m_movie.play();
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
