#ifndef __LOADING_SYS__
#define __LOADING_SYS__

#include "system/ISystem.hpp"

class LoadingSys
	: public ISystem
{
public:
	void Update(entt::registry& reg) override;
};

#endif