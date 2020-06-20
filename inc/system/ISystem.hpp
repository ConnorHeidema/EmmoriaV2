#ifndef __ISYSTEM__
#define __ISYSTEM__

#include <entt/entt.hpp>

class ISystem
{
public:
	ISystem() {};
	virtual void Initialize(entt::registry& reg) {}
	virtual void Update(entt::registry& /*reg*/) = 0;
	virtual bool IsEnabled(entt::registry& /*reg*/) { return true; }
	virtual ~ISystem() {};
};

#endif