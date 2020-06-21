#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/IGraphicsSystem.hpp"

class DialogSys
	: public IGraphicsSystem
{
public:
	void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> /*pRenderWindow*/) override;
};

#endif