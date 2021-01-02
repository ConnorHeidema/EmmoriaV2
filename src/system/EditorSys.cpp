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

#include "config/ConfigItems.hpp"
#include "util/SystemList.hpp"

EditorSys::EditorSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, m_rReg(rReg)
	, m_rRenderWindow(rRenderWindow)
{ }

// This needs to parse a file based on the location, open that file and when the user scrolls allow the user to place things
// in a certain file onto the screen. It needs to tell whether what you are placing is on a tilemap or not.
// Finally it should write those contents to a temp file and allow it to be saved if the user selects an action.
// This should only work if a certain config item is set to true AllowEditing
void EditorSys::Update_()
{
	std::cout << "inside " << SystemList::m_pSystemList[static_cast<int>(SystemId_t::Movement_t)]->GetName() << std::endl;
}
