#ifndef __PRINT_MOVEMENT_SYS__
#define __PRINT_MOVEMENT_SYS__

#include "system/ISystem.hpp"

#include "component/PlayerComp.hpp"
#include "component/PositionComp.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

class PrintMovementSys
	: public ISystem
{
public:
	void Update(entt::registry& reg) override
	{
		reg.view<PositionComp>().each([](auto entity, auto &posComp) {
			std::cout << std::to_string(posComp.position.x) << std::endl << std::to_string(posComp.position.y) << std::endl << std::endl;

		});
	}
};

#endif