#include "system/MovieRenderSys.hpp"

#include "component/MovieComp.hpp"
#include "component/LoadComp.hpp"

#include "util/Entitymap.hpp"
#include "util/MediatoEntitymap.hpp"

void MovieRenderSys::Initialize(entt::registry& reg)
{
	auto movie = reg.create();
	auto& media = reg.emplace<MovieComp>(movie);
	media.m_currentMedia = Media_t::INTRO_MOVIE;
	m_lastMedia = Media_t::NONE;
}

void MovieRenderSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	reg.view<MovieComp>().each([&](auto entity, auto &movieComp)
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
			pRenderWindow->draw(m_movie);
		}
		else if (movieComp.m_currentMedia != Media_t::NONE)
		{
			reg = {};
			auto loadEntity = reg.create();
			auto& load = reg.emplace<LoadComp>(loadEntity);
			load.filePath = MediatoEntitymap::m_mediatoEntitymap.at(movieComp.m_currentMedia);
			m_lastMedia = Media_t::NONE;
		}
	});
}
