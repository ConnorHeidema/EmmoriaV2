#include "util/SystemList.hpp"

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

std::list<std::shared_ptr<ISystem>> SystemList::CreateSystemList(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
{
	std::list<std::shared_ptr<ISystem>> m_sysRunningOrder
	{
		std::make_unique<MovementSys>(rReg),
		std::make_unique<PrintMovementSys>(rReg),
		std::make_unique<TileMapSys>(rReg, rRenderWindow),
		std::make_unique<MovieRenderSys>(rReg, rRenderWindow),
		std::make_unique<GameRenderSys>(rReg, rRenderWindow),
		std::make_unique<LoadingSys>(rReg),
		std::make_unique<ButtonSys>(rReg),
		std::make_unique<ClickableSys>(rReg),
		std::make_unique<DialogSys>(rReg),
		std::make_unique<PersistentSys>(rReg),
		std::make_unique<HealthSys>(rReg),
		std::make_unique<InteractingSys>(rReg)
	};
	return m_sysRunningOrder;
}

std::list<std::shared_ptr<ISystem>> SystemList::m_pSystemList =
{

};