#ifndef __BLOB_SYS__
#define __BLOB_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

class BlobSys
	: public System
{
public:
	BlobSys(std::string systemConfigItem, entt::registry& rReg);

private:
	void Update_() override;
	entt::registry& m_rReg;
	static int const mk_sightDistance;
	static int const mk_blobSpeed;
};

#endif