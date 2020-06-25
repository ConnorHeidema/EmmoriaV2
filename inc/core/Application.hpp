#ifndef __APPLICATION__
#define __APPLICATION__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

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
};

#endif