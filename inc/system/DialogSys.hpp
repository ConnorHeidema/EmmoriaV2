#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/System.hpp"

#include <entt/entt.hpp>

enum DialogSysState_t
{
	WAITING,
	PRODUCING,
	PENDING,
	LOADING,
	FINISHED
};

class DialogSys
	: public System
{
public:
	DialogSys(std::string systemConfigItem, entt::registry& reg);

private:
	void Update_() override;

	void UpdateWaitingState_();
	void UpdateProducingState_();
	void UpdatePendingState_();
	void UpdateLoadingState_();
	void UpdateFinishedState_();

	entt::registry& m_rReg;

	DialogSysState_t m_dialogSysState;
};

#endif