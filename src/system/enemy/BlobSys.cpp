#include "system/enemy/BlobSys.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/PositionComp.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include "util/AnimationMappings.hpp"

#include <math.h>

float const BlobSys::mk_sightDistance = 300;
float const BlobSys::mk_blobSpeed = 1;

BlobSys::BlobSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void BlobSys::Update_()
{
	m_rReg.view<PlayerComp, PositionComp>().each([&](auto playerEntity, auto& playerPositionComp)
	{
		m_rReg.view<BlobComp, PositionComp>().each([&](auto blobEntity, auto& blobPositionComp)
		{
			if (std::abs(playerPositionComp.m_position.x - blobPositionComp.m_position.x) < mk_sightDistance &&
				std::abs(playerPositionComp.m_position.y - blobPositionComp.m_position.y) < mk_sightDistance)
			{
				float angle = atan2(
					playerPositionComp.m_position.y - blobPositionComp.m_position.y,
					playerPositionComp.m_position.x - blobPositionComp.m_position.x);
				blobPositionComp.m_position.x += mk_blobSpeed * cos(angle);
				blobPositionComp.m_position.y += mk_blobSpeed * sin(angle);
			}
		});
	});
}