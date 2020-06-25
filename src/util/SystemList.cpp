#include "util/SystemList.hpp"

#include "system/MovementSys.hpp"
#include "system/PrintMovementSys.hpp"
#include "system/MovieRenderSys.hpp"
#include "system/GameRenderSys.hpp"
#include "system/LoadingSys.hpp"
#include "system/ClickableSys.hpp"
#include "system/DialogSys.hpp"

std::list<std::shared_ptr<ISystem>> SystemList::CreateSystemList(entt::registry& m_reg, sf::RenderWindow& m_renderWindow)
{
	std::list<std::shared_ptr<ISystem>> m_sysList
	{
		std::make_unique<MovementSys>(m_reg),
		std::make_unique<PrintMovementSys>(m_reg),
		std::make_unique<MovieRenderSys>(m_reg, m_renderWindow),
		std::make_unique<GameRenderSys>(m_reg, m_renderWindow),
		std::make_unique<LoadingSys>(m_reg),
		std::make_unique<ClickableSys>(m_reg),
		std::make_unique<DialogSys>(m_reg, m_renderWindow)
	};
	return m_sysList;
}

std::list<std::shared_ptr<ISystem>> SystemList::m_pSystemList = {};