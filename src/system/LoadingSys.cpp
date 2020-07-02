#include "system/LoadingSys.hpp"

#include "component/functional/LoadComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/Entitymap.hpp"

#include <entt/entt.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

LoadingSys::LoadingSys(entt::registry& rReg)
	: m_rReg(rReg)
{}

void LoadingSys::Update()
{
	m_rReg.view<LoadComp>().each([&](auto entity, auto& loadComp)
	{
		std::string token;
		std::ifstream file(ApplicationParameters::k_dataPath + loadComp.m_filePath);
		std::cout << "Loading entity from file " + loadComp.m_filePath << std::endl;
		while(std::getline(file, token))
		{
			std::cout << "Loading new entity" << std::endl;
			auto loadEntity = m_rReg.create();
			std::istringstream line(token);
			while (!line.eof())
			{
				line >> token;
				std::cout << "Attaching " + token + " parameter to entity" << std::endl;
				Entitymap::m_entityMap.at(token)(m_rReg, loadEntity, line);
			}
		}
		m_rReg.destroy(entity);
	});
}
