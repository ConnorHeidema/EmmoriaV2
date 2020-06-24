#ifndef __ISYSTEM__
#define __ISYSTEM__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

class ISystem
{
public:
	ISystem() {};
	virtual void Update() = 0;
	virtual ~ISystem() {};
};

#endif