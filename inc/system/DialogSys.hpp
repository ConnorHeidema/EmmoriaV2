#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/ISystem.hpp"

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
	: public ISystem
{
public:
	DialogSys(entt::registry& reg);
	void Update() override;

private:
	void UpdateWaitingState_();
	void UpdateProducingState_();
	void UpdatePendingState_();
	void UpdateLoadingState_();
	void UpdateFinishedState_();

	entt::registry& m_rReg;

	DialogSysState_t m_dialogSysState;
};

#endif