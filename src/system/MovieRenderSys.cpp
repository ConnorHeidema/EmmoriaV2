#include "system/MovieRenderSys.hpp"

#include "component/MovieComp.hpp"

#include "util/Mediamap.hpp"

MovieRenderSys::MovieRenderSys()
{
	m_movie.openFromFile(Mediamap::m_mediamap.at(Media_t::INTRO_MOVIE));
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
		m_movie.update();
		if (m_movie.getStatus() != sfe::End)
		{
			pRenderWindow->draw(m_movie);
		}
	});
}