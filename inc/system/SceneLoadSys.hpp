#ifndef __SCENE_LOAD_SYS__
#define __SCENE_LOAD_SYS__

#include "system/System.hpp"

#include "component/functional/LocationComp.hpp"

#include <entt/entt.hpp>

class SceneLoadSys
	: public System
{
public:
	SceneLoadSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;
	entt::registry& m_rReg;
	std::string m_lastArea;
};

#endif