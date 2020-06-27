#include "system/PrintMovementSys.hpp"

#include "component/functional/PositionComp.hpp"

#include <iostream>

PrintMovementSys::PrintMovementSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void PrintMovementSys::Update()
{
	// reg.view<PositionComp>().each([](auto entity, auto &posComp) {
	// 	std::cout << "(" <<
	// 		std::to_string(posComp.position.x) <<
	// 		", " <<
	// 		std::to_string(posComp.position.y) << ")" <<
	// 		std::endl;
	// });
}