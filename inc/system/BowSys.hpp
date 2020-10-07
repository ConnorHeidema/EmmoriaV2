#ifndef __BOW_SYS__
#define __BOW_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class BowSys
	: public System
{
public:
	BowSys(std::string systemConfigItem, entt::registry& rReg);
private:
	void Update_() override;

	entt::registry& m_rReg;

	entt::entity m_entity;

	int m_bowCllickLatch;

	static const int mk_frequency;
	static const int mk_arrowWidthUnits;
	static const int mk_arrowHeightUnits;
};

#endif