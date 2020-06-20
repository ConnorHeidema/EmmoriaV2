#ifndef __MOVIE_RENDER_SYS__
#define __MOVIE_RENDER_SYS__

#include "system/IGraphicsSystem.hpp"

#include <sfeMovie/Movie.hpp>

class MovieRenderSys
	: public IGraphicsSystem
{
public:
	MovieRenderSys();

	void Initialize(entt::registry& reg) override;

	void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow) override;

    sfe::Movie m_movie;
};

#endif