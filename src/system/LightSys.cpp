#include "system/LightSys.hpp"

#include "ltbl/lighting/LightShape.h"

#include <iostream>

LightSys::LightSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg) 
{
}

void LightSys::Update_()
{
	// to be removed when light works on ubuntu
	ltbl::LightShape light;
	std::cout << "in light sys" << std::endl;
}
