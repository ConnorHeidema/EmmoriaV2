#include "util/SystemList.hpp"

#include "system/ConfigSys.hpp"
#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
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

#include "system/enemy/BlobSys.hpp"

#define REGULAR_SYSTEM_NAME_INPUT(System) std::make_unique< System##Sys>( \
	std::string("Disable") + \
	std::string(#System) + \
	std::string("Sys"), \
	rReg)

#define ANIMATION_SYSTEM_NAME_INPUT(System)	std::make_unique< System##Sys>( \
	std::string("Disable") + \
	std::string(#System) + \
	std::string("Sys"), \
	rReg, \
	rRenderWindow)

std::list<std::shared_ptr<System>> SystemList::CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
{
	std::list<std::shared_ptr<System>> m_sysRunningOrder
	{
		REGULAR_SYSTEM_NAME_INPUT(Config),
		REGULAR_SYSTEM_NAME_INPUT(Movement),
		REGULAR_SYSTEM_NAME_INPUT(PrintMovement),
		REGULAR_SYSTEM_NAME_INPUT(TileMap),
		REGULAR_SYSTEM_NAME_INPUT(Interacting),
		REGULAR_SYSTEM_NAME_INPUT(Animation),
		REGULAR_SYSTEM_NAME_INPUT(Loading),
		REGULAR_SYSTEM_NAME_INPUT(Button),
		REGULAR_SYSTEM_NAME_INPUT(Clickable),
		REGULAR_SYSTEM_NAME_INPUT(Dialog),
		REGULAR_SYSTEM_NAME_INPUT(Persistent),
		REGULAR_SYSTEM_NAME_INPUT(Health),
		REGULAR_SYSTEM_NAME_INPUT(SceneLoad),
		ANIMATION_SYSTEM_NAME_INPUT(GameRender),
		ANIMATION_SYSTEM_NAME_INPUT(MovieRender),
		REGULAR_SYSTEM_NAME_INPUT(Blob),
		REGULAR_SYSTEM_NAME_INPUT(Bow)
	};
	return m_sysRunningOrder;
}

#undef ANIMATION_SYSTEM_NAME_INPUT
#undef REGULAR_SYSTEM_NAME_INPUT

std::list<std::shared_ptr<System>> SystemList::m_pSystemList =
{

};