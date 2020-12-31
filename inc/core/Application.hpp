#ifndef __APPLICATION__
#define __APPLICATION__

#include <entt/entt.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	Application();
	bool Start();

private:
	void Initialize_();
	void RunLoop_();
	void CheckForEvents_();
	bool UpdateWhenNotFocused_();

	entt::registry m_reg;
	sf::RenderWindow m_renderWindow;

	std::string const m_kOnlyWhenFocused;
};

#endif