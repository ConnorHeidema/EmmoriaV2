#ifndef __RENDER_SYS__
#define __RENDER_SYS__

#include "system/IGraphicsSystem.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/MovieComp.hpp"

#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

class RenderSystem
	: public IGraphicsSystem
{
public:
	RenderSystem()
	{
		m_movie.openFromFile(MediaMap::m_mediaMap.at(Media_t::INTRO_MOVIE));
		m_movie.play();
	}

	void Update(entt::registry& reg, sf::RenderWindow& gameWindow) override
	{

		gameWindow.clear();
		reg.view<MovieComp>().each([&](auto entity, auto &movieComp)
		{
			m_movie.update();
			if (m_movie.getStatus() != sfe::End)
			{
				gameWindow.draw(m_movie);
			}
		});
		reg.view<PositionComp, RenderableComp>().each([&gameWindow](auto entity, auto &posComp)
		{
			auto a = sf::RectangleShape(sf::Vector2f(20,20));
			a.setFillColor(sf::Color::Green);
			a.setPosition(posComp.position.x, posComp.position.y);
			gameWindow.draw(a);
		});
		gameWindow.display();
	}

    sfe::Movie m_movie;
private:
};

#endif