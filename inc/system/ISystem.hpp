#ifndef __ISYSTEM__
#define __ISYSTEM__

#include <entt/entt.hpp>

class ISystem
{
public:
	ISystem() {};
	virtual void Update(entt::registry& reg) = 0;
	virtual ~ISystem() {};
};

#endif