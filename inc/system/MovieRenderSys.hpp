#ifndef __MOVIE_RENDER_SYS__
#define __MOVIE_RENDER_SYS__

#include "system/IGraphicsSystem.hpp"

#include "util/Mediamap.hpp"

#include <sfeMovie/Movie.hpp>

class MovieRenderSys
	: public IGraphicsSystem
{
public:

	void Initialize(entt::registry& reg) override;

	void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow) override;

	Media_t m_lastMedia;
    sfe::Movie m_movie;
};

#endif