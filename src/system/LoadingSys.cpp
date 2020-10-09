#include "system/LoadingSys.hpp"

#include "component/functional/LoadComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/Entitymap.hpp"

#include <entt/entt.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

LoadingSys::LoadingSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{}

void LoadingSys::Update_()
{
	m_rReg.view<LoadComp>().each([&](auto entity, auto& loadComp)
	{
		std::string token;
		std::ifstream file(ApplicationParameters::k_dataPath + loadComp.m_filePath);
		std::cout << "Loading entity from file " << loadComp.m_filePath << std::endl;
		while(std::getline(file, token))
		{
			//std::cout << "Loading new entity" << std::endl;
			auto loadEntity = m_rReg.create();
			std::istringstream line(token);
			while (!line.eof())
			{
				line >> token;
				//std::cout << "\tAttaching " << token << " parameter to entity" << std::endl;
				if (Entitymap::m_entityMap.find(token) != Entitymap::m_entityMap.end())
				{
					Entitymap::m_entityMap.at(token)(m_rReg, loadEntity, line);
				}
				else
				{
					m_rReg.destroy(loadEntity);
					if (token != "")
					{
						std::cout << "\tCould not attach " << token << " parameter to entity" << std::endl;
					}
					break;
				}
			}
		}
		m_rReg.destroy(entity);
	});
}
