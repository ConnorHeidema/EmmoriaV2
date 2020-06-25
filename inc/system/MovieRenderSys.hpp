#ifndef __MOVIE_RENDER_SYS__
#define __MOVIE_RENDER_SYS__

#include "system/ISystem.hpp"

#include "util/Mediamap.hpp"

#include <sfeMovie/Movie.hpp>

#include <entt/entt.hpp>

#include <memory>

class MovieRenderSys
	: public ISystem
{
public:
	MovieRenderSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow);
	void Update() override;

private:
	sf::RenderWindow& m_rRenderWindow;
	entt::registry& m_rReg;

	Media_t m_lastMedia;
    sfe::Movie m_movie;
};

#endif