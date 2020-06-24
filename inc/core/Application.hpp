#ifndef __APPLICATION__
#define __APPLICATION__

#include "system/ISystem.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include <memory>
#include <list>

class Application
{
public:
	Application();
	bool Start();

private:
	void Initialize_();
	void RunLoop_();
	void CheckForEvents_();

	entt::registry m_reg;
	sf::RenderWindow m_renderWindow;

	std::list<std::shared_ptr<ISystem>> m_pSystems;
};

#endif