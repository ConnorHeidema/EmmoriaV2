#include "system/LoadingSys.hpp"

#include "component/LoadComp.hpp"

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
	m_rReg.view<LoadComp>().each([&](auto entity, auto &loadComp) {
		std::string token;
		std::ifstream file(ApplicationParameters::k_dataPath + loadComp.filePath);
		std::cout << ApplicationParameters::k_dataPath + loadComp.filePath;
		while(std::getline(file, token))
		{
			std::istringstream line(token);
			line >> token;
			std::cout << "Loading from file: " + ApplicationParameters::k_dataPath + loadComp.filePath << std::endl;
			Entitymap::m_entityMap.at(token)(m_rReg, line);
		}
		m_rReg.destroy(entity);
	});
}
