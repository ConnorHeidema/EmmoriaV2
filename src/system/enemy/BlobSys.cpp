#include "system/enemy/BlobSys.hpp"

#include "component/tag/AllTagComp.hpp"
#include "component/functional/PositionComp.hpp"

#include "TileMap/TileMapIndexes.hpp"

#include "util/AnimationMappings.hpp"

#include <entt/entt.hpp>

#include <math.h>

float const BlobSys::mk_sightDistance = 300;
float const BlobSys::mk_blobSpeed = 1;

BlobSys::BlobSys(std::string systemConfigItem, entt::registry& rReg)
	: System(systemConfigItem)
	, m_rReg(rReg)
{ }

void BlobSys::Update_()
{
}