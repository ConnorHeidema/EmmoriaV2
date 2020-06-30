#include "system/InteractingSys.hpp"

#include "component/functional/PositionComp.hpp"

#include <iostream>

InteractingSys::InteractingSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void InteractingSys::Update()
{
	// reg.view<PositionComp>().each([](auto entity, auto& posComp) {
	// 	std::cout << "(" <<
	// 		std::to_string(posComp.position.x) <<
	// 		", " <<
	// 		std::to_string(posComp.position.y) << ")" <<
	// 		std::endl;
	// });
}