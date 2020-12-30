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

#include "system/enemy/BlobSys.hpp"

#define STD_MAKE_UNIQUE_SYS(System) std::make_unique< System##Sys>( \
	std::string("Disable") + \
	std::string(#System) + \
	std::string("Sys"), \
	rReg)

#define STD_MAKE_UNIQUE_ANIMATION_SYS(System)	std::make_unique< System##Sys>( \
	std::string("Disable") + \
	std::string(#System) + \
	std::string("Sys"), \
	rReg, \
	rRenderWindow)

std::list<std::shared_ptr<System>> SystemList::CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
{
	std::list<std::shared_ptr<System>> m_sysRunningOrder
	{
		STD_MAKE_UNIQUE_SYS(Reboot),
		STD_MAKE_UNIQUE_SYS(Config),
		STD_MAKE_UNIQUE_SYS(Reload),
		STD_MAKE_UNIQUE_SYS(Movement),
		STD_MAKE_UNIQUE_SYS(TileMap),
		STD_MAKE_UNIQUE_SYS(Loading),
		STD_MAKE_UNIQUE_SYS(Button),
		STD_MAKE_UNIQUE_SYS(Clickable),
		STD_MAKE_UNIQUE_SYS(Dialog),
		STD_MAKE_UNIQUE_SYS(Persistent),
		STD_MAKE_UNIQUE_SYS(Health),
		STD_MAKE_UNIQUE_SYS(SceneLoad),
		STD_MAKE_UNIQUE_SYS(Interacting),
		STD_MAKE_UNIQUE_SYS(Animation),
		STD_MAKE_UNIQUE_ANIMATION_SYS(GameRender),
		STD_MAKE_UNIQUE_ANIMATION_SYS(MovieRender),
		STD_MAKE_UNIQUE_SYS(Blob),
		STD_MAKE_UNIQUE_SYS(Bow),
		STD_MAKE_UNIQUE_SYS(Lifespan),
		STD_MAKE_UNIQUE_SYS(Door),
		STD_MAKE_UNIQUE_SYS(Switch),
		STD_MAKE_UNIQUE_SYS(Music),
	};
	return m_sysRunningOrder;
}

#undef ANIMATION_SYSTEM_NAME_INPUT
#undef REGULAR_SYSTEM_NAME_INPUT

std::list<std::shared_ptr<System>> SystemList::m_pSystemList = {};