#ifndef __SCENE_LOAD_SYS__
#define __SCENE_LOAD_SYS__

#include "system/ISystem.hpp"

#include "component/functional/LocationComp.hpp"

#include <entt/entt.hpp>

class SceneLoadSys
	: public ISystem
{
public:
	SceneLoadSys(entt::registry& reg);
	void Update() override;

private:
	entt::registry& m_rReg;
	std::string m_lastArea;
};

#endif