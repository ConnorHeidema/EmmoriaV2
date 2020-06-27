#include "system/ButtonSys.hpp"

#include "component/functional/ClickableComp.hpp"
#include "component/functional/MovieComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/PositionComp.hpp"

#include "util/Mediamap.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

ButtonSys::ButtonSys(entt::registry& rReg)
	: m_rReg(rReg)
{ }

void ButtonSys::Update()
{
}