#ifndef __SWORD_SYS__
#define __SWORD_SYS__

#include "system/System.hpp"

#include "util/Latch.hpp"
#include <entt/fwd.hpp>

class PositionComp;
class ClickableComp;

class SwordSys
	: public System
{
public:
	SwordSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;
	void CreateSword_(
		PositionComp& playerPositionComp,
		ClickableComp& clickableActionArea);

	entt::registry& m_rReg;

	Latch m_swordFrequencyLatch;

	static const int mk_frequency;
	static const int mk_arrowWidthUnits;
	static const int mk_arrowHeightUnits;
};

#endif