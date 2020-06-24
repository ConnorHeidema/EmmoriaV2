#ifndef __LOADING_SYS__
#define __LOADING_SYS__

#include "system/ISystem.hpp"

class LoadingSys
	: public ISystem
{
public:
	LoadingSys(entt::registry& reg);
	void Update() override;
private:
	entt::registry& m_rReg;
};

#endif