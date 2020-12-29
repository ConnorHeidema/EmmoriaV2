#ifndef __MOVIE_RENDER_SYS__
#define __MOVIE_RENDER_SYS__

#include "system/System.hpp"

#include "util/Mediamap.hpp"

#include <sfeMovie/Movie.hpp>

#include <memory>

class MovieRenderSys
	: public System
{
public:
	MovieRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow);

private:
	void Update_() override;
	void CreateMovieEntity_();
	sf::RenderWindow& m_rRenderWindow;
	entt::registry& m_rReg;

	Media_t m_lastMedia;
    sfe::Movie m_movie;
};

#endif
