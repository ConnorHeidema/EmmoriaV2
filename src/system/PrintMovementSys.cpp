#include "system/PrintMovementSys.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"

#include <iostream>

void PrintMovementSys::Update(entt::registry& reg)
{
	reg.view<PositionComp>().each([](auto entity, auto &posComp) {
		std::cout << std::to_string(posComp.position.x) << std::endl << std::to_string(posComp.position.y) << std::endl << std::endl;

	});
}