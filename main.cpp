#include "util/Size.hpp"

#include "core/Application.hpp"
#include "config/ConfigItems.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

// new includes for test
#include <sstream>
#include <string>
#include <cstdint>
#include <list>
#include <memory>

static std::string const k_actualText =
    "*person* Trained for defence, imbued with a spirit to fight. We are the last line of defence"
    " against the demon of this world. The Vulcan. "
    "*mystery* Welcome all to the show. Today we watch"
    " as yet another candidate fights for his life to survive the perilous pit of no return."
    " Shall he survive? Lets watch! "
    "*person* where am I? "
    "|Files/0,0|";

static std::string const k_testText =
    "*person* Trained for defence, imbued with a spirit to fight. We are the last line of defence"
    " against the demon of this world. The Vulcan. I have a lot more to say to test this properly so I will writ it right here and right now "
    "*mystery* Welcome all to the show. Today we watch yooooooo this is a thing I need to do to say things and such to see if things are correct"
    " as yet another candidate fights for his life to survive the perilous pit of no return."
    " Shall he survive? Lets watch! "
    "*person* where am I? "
    "|Files/0,0|";


class DialogSysTest
{
public:
    DialogSysTest();
    void Process(sf::RenderWindow& rRenderWindow);
private:
    void ProcessWaiting(sf::RenderWindow& rRenderWindow);
    void ProcessProducing(sf::RenderWindow& rRenderWindow);
    void ProcessFinished(sf::RenderWindow& rRenderWindow);

    class DialogContainer
    {
    public:
        std::string portraitName;
        std::list<std::string> contentList;
    };
    std::list<DialogContainer> m_dialogContainerList;
    enum class State_t
    {
        WAITING,
        PRODUCING,
        FINISHED
    } m_state;
};

static DialogSysTest s_DialogSysTest;

void CheckForEvents_(sf::RenderWindow& rRenderWindow)
{
	sf::Event event;
	while (rRenderWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: rRenderWindow.close(); break;
			case sf::Event::GainedFocus: break;
			case sf::Event::LostFocus:  break;
			default: break;
		}
	}
}

void RunLoop_(sf::RenderWindow& rRenderWindow)
{
	rRenderWindow.clear();

    s_DialogSysTest.Process(rRenderWindow);

	rRenderWindow.display();
	CheckForEvents_(rRenderWindow);
}

int main(int argc, char ** argv)
{
    DialogSysTest d;
    uint32_t height = 8;
    sf::RenderWindow renderWindow(sf::VideoMode(
            sf::VideoMode::getDesktopMode().width,
            sf::VideoMode::getDesktopMode().height),
			"test",
			sf::Style::Fullscreen);
    while (renderWindow.isOpen()) { {RunLoop_(renderWindow);}; }

	// Application app;
    // app.Start() ?
    //     std::cout << "Successfully exited game." :
    //     std::cout << "Error occurred while exiting game";
    // std::cout << std::endl;
}

DialogSysTest::DialogSysTest()
    : m_state(State_t::WAITING)
{}

void DialogSysTest::Process(sf::RenderWindow& rRenderWindow)
{
    switch (m_state)
    {
        case State_t::WAITING: ProcessWaiting(rRenderWindow); return;
        case State_t::PRODUCING: ProcessProducing(rRenderWindow); return;
        case State_t::FINISHED: ProcessFinished(rRenderWindow); return;
        default: std::cout << "ERROR" << std::endl; return;
    }
}

void DialogSysTest::ProcessWaiting(sf::RenderWindow& rRenderWindow)
{
    std::list<DialogContainer> firstPassDialogContainer;
    std::istringstream iss(k_testText);
    std::shared_ptr<DialogContainer> m_pDialogContainer;
    int maxWidthForText = 1620;
    int textHeight = 50;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf");
    do
    {
        std::string subs;
        iss >> subs;

        if (subs.front() == '*' && subs.back() == '*')
        {
            if (m_pDialogContainer)
            {
                m_dialogContainerList.emplace_back(*m_pDialogContainer);
            }
            m_pDialogContainer = std::make_shared<DialogContainer>();
            m_pDialogContainer->portraitName = subs.substr(1, subs.length() - 2);
            m_pDialogContainer->contentList = std::list<std::string>({""});
            continue;
        }
        if (subs.front() == '|' && subs.back() == '|')
        {
            m_dialogContainerList.emplace_back(*m_pDialogContainer);
            break;
        }
        sf::Text testText(m_pDialogContainer->contentList.back(), font, textHeight);
        int textActualWidth = testText.getLocalBounds().width;
        if (textActualWidth > maxWidthForText)
        {
            m_pDialogContainer->contentList.push_back("");
        }
        m_pDialogContainer->contentList.back() += std::string(" ") + subs;
    }
    while (iss);
    std::cout << m_dialogContainerList.front().contentList.back() << std::endl;
    // Second Pass
}

void DialogSysTest::ProcessProducing(sf::RenderWindow& rRenderWindow)
{


    //sf::Text text(k_testText, font, textHeight);
    //uint32_t textWidth = text.getLocalBounds().width;

}

void DialogSysTest::ProcessFinished(sf::RenderWindow& rRenderWindow)
{

}