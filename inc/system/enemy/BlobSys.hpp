#ifndef __BLOB_SYS__
#define __BLOB_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>
class BlobSys
	: public System
{
public:
	BlobSys(std::string systemConfigItem, entt::registry& rReg);

private:
	void Update_() override;
	entt::registry& m_rReg;
	static float const mk_sightDistance;
	static float const mk_blobSpeed;
};

#endif