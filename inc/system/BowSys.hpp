#ifndef __BOW_SYS__
#define __BOW_SYS__

#include "system/System.hpp"

#include "component/functional/PositionComp.hpp"
#include "component/functional/ClickableComp.hpp"

#include "util/Latch.hpp"

class BowSys
	: public System
{
public:
	BowSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;
	void CreateArrow_(
		PositionComp& playerPositionComp,
		ClickableComp& clickableActionArea);

	entt::registry& m_rReg;

	entt::entity m_entity;

	Latch m_bowFrequencyLatch;

	static const int mk_frequency;
	static const int mk_arrowWidthUnits;
	static const int mk_arrowHeightUnits;
};

#endif