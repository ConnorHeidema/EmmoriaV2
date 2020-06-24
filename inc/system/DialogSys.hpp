#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/IGraphicsSystem.hpp"
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
	: public IGraphicsSystem
{
public:
	DialogSys();
	void Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> /*pRenderWindow*/) override;

private:
	void PresentingUpdate_(std::shared_ptr<sf::RenderWindow> /*pRenderWindow*/);
	void WaitingUpdate_(entt::registry& reg);
	void ConsumingUpdate_();

	void DelimitText_(std::string& text);

	int m_curClickFrame;
	std::list<std::string> m_currentDialogList;
	Size m_curSize;
	Position m_curPosition;
	DialogSysState m_dialogSysState;
};

#endif