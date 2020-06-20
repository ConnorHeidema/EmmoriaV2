#ifndef __IGRAPHICS_SYSTEM__
#define __IGRAPHICS_SYSTEM__

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

class IGraphicsSystem
{
public:
	IGraphicsSystem() {};
	virtual void Initialize(entt::registry& reg) {}
	virtual void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> /*pRenderWindow*/) = 0;
	virtual bool IsEnabled() { return true; }
	virtual ~IGraphicsSystem() {};
};

#endif