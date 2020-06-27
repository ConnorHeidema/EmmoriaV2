#include "system/DialogSys.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/ClickableComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/MouseUtils.hpp"
#include "util/Helper.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

DialogSys::DialogSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rRenderWindow(rRenderWindow)
	, m_rReg(rReg)
{}

void DialogSys::Update()
{

}
