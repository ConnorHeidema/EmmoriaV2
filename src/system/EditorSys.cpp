#include "system/EditorSys.hpp"

#include "component/tag/AllTagComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SpriteComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/TileMapPtrComp.hpp"
#include "component/functional/HealthComp.hpp"
#include "component/functional/RotationComp.hpp"
#include "component/functional/DialogComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/stats/MaxHealthComp.hpp"
#include "component/functional/SoundComp.hpp"

#include "util/Mediamap.hpp"
#include "util/ApplicationParameters.hpp"
#include "util/Helper.hpp"
#include "util/TextureContainer.hpp"
#include "util/FontContainer.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include <SFML/Audio/Music.hpp>

#include <math.h>

#include <iostream>

EditorSys::EditorSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

void EditorSys::Update_()
{
	std::cout << "inside editorsys" << std::endl;
}