#ifndef __BLOB_SYS__
#define __BLOB_SYS__

#include "system/ISystem.hpp"

#include <entt/entt.hpp>

class BlobSys
	: public ISystem
{
public:
	BlobSys(entt::registry& rReg);
	void Update() override;
private:
	entt::registry& m_rReg;
	static int const mk_sightDistance;
	static int const mk_blobSpeed;
};

#endif