#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/ISystem.hpp"
#include "util/Size.hpp"
#include "util/Position.hpp"

#include <list>

enum DialogSysState
{
	WAITING,
	CONSUMING,
	PRESENTING
};

class DialogSys
	: public ISystem
{
public:
	DialogSys(entt::registry& reg, sf::RenderWindow& rRenderWindow);
	void Update() override;

private:
	void PresentingUpdate_();
	void WaitingUpdate_();
	void ConsumingUpdate_();

	void DelimitText_(std::string& text);

	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;

	int m_curClickFrame;
	std::list<std::string> m_currentDialogList;
	Size m_curSize;
	Position m_curPosition;
	DialogSysState m_dialogSysState;
};

#endif