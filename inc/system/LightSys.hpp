#ifndef __LIGHT_SYS__
#define __LIGHT_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>
#include <memory>

namespace sf { class RenderWindow; }

class LightSys
	: public System {
public:
	LightSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow);
private:
	void Update_() override;

	struct Impl;
	std::unique_ptr<Impl> pImpl;
};

#endif