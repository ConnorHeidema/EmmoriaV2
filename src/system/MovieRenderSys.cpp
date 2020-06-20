#include "system/MovieRenderSys.hpp"

#include "component/MovieComp.hpp"
#include "component/LoadComp.hpp"

#include "util/Entitymap.hpp"
#include "util/MediatoEntitymap.hpp"

MovieRenderSys::MovieRenderSys() : m_currentMedia(Media_t::INTRO_MOVIE)
{
	m_movie.openFromFile(Mediamap::m_mediamap.at(m_currentMedia));
	m_movie.play();
}

void MovieRenderSys::Initialize(entt::registry& reg)
{
	auto movie = reg.create();
	reg.emplace<MovieComp>(movie);
}

void MovieRenderSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	reg.view<MovieComp>().each([&](auto entity, auto &movieComp)
	{
		if (m_movie.getStatus() != sfe::Stopped)
		{
			m_movie.update();
			pRenderWindow->draw(m_movie);
		}
		else if (m_currentMedia != Media_t::NONE)
		{
			reg = {};
			auto loadEntity = reg.create();
			auto& load = reg.emplace<LoadComp>(loadEntity);
			load.filePath = MediatoEntitymap::m_mediatoEntitymap.at(m_currentMedia);
			m_currentMedia = Media_t::NONE;
		}
	});
}
