#ifndef __DIALOG_SYS__
#define __DIALOG_SYS__

#include "system/System.hpp"

#include <SFML/Graphics.hpp>
#include <entt/fwd.hpp>

#include <list>
#include <memory>

class DialogSys
	: public System
{
public:
	DialogSys(std::string systemConfigItem, entt::registry& reg);
private:
	void Update_() override;

	void ProcessWaiting();
    void ProcessProducing();
    void ProcessFinished();

    class DialogContainer
    {
    public:
        std::string portraitName;
        std::list<std::list<std::string>> contentList;
        std::string nextFileToLoad;
    };
    std::list<DialogContainer> m_dialogContainerList;
    enum class State_t
    {
        WAITING,
        PRODUCING,
        FINISHED
    } m_state;
    int mTimer;
    int const k_mMaxTimer;
 	entt::registry& m_rReg;
	sf::Font m_font;
    std::shared_ptr<DialogContainer> m_pDialogContainer;
};

#endif