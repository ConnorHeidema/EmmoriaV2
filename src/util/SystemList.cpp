#include "util/SystemList.hpp"

#include "system/RebootSys.hpp"
#include "system/ReloadSys.hpp"
#include "system/ConfigSys.hpp"
#include "system/MovementSys.hpp"
#include "system/MovieRenderSys.hpp"
#include "system/GameRenderSys.hpp"
#include "system/LoadingSys.hpp"
#include "system/ButtonSys.hpp"
#include "system/ClickableSys.hpp"
#include "system/DialogSys.hpp"
#include "system/PersistentSys.hpp"
#include "system/HealthSys.hpp"
#include "system/InteractingSys.hpp"
#include "system/TileMapSys.hpp"
#include "system/AnimationSys.hpp"
#include "system/SceneLoadSys.hpp"
#include "system/BowSys.hpp"
#include "system/LifespanSys.hpp"
#include "system/DoorSys.hpp"
#include "system/SwitchSys.hpp"
#include "system/MusicSys.hpp"
#include "system/EditorSys.hpp"

#include "system/enemy/BlobSys.hpp"

#include "system/SystemMacro.hpp"
std::vector<std::shared_ptr<System>> SystemList::CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
{
	std::vector<std::shared_ptr<System>> m_sysRunningOrder
	{
		DO_MACRO_FOR_ALL_SYSTEMS(STD_MAKE_UNIQUE_SYS, STD_MAKE_UNIQUE_ANIMATION_SYS)
	};
	return m_sysRunningOrder;
}
#include "system/SystemMacroEnd.hpp"

std::vector<std::shared_ptr<System>> SystemList::m_pSystemList = {};