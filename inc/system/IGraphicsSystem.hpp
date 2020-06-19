#ifndef __IGRAPHICS_SYSTEM__
#define __IGRAPHICS_ISYSTEM__

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

class IGraphicsSystem
{
public:
	IGraphicsSystem() {};
	virtual void Update(entt::registry& reg, sf::RenderWindow& gameWindow) = 0;
	virtual ~IGraphicsSystem() {};
};

#endif