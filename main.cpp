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
#include <iterator>

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
        std::list<std::list<std::string>> contentList;
    };
    std::list<DialogContainer> m_dialogContainerList;
    enum class State_t
    {
        WAITING,
        PRODUCING,
        FINISHED
    } m_state;

    sf::Font m_font;
    int m_maxWidthForText;
    int m_textHeight;
    int mTimer;
    int const k_mMaxTimer;
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
    renderWindow.setFramerateLimit(60);
    while (renderWindow.isOpen()) { {RunLoop_(renderWindow);}; }

	// Application app;
    // app.Start() ?
    //     std::cout << "Successfully exited game." :
    //     std::cout << "Error occurred while exiting game";
    // std::cout << std::endl;
}

DialogSysTest::DialogSysTest()
    : m_state(State_t::WAITING)
    , m_maxWidthForText(1370)
    , m_textHeight(50)
    , mTimer(0)
    , k_mMaxTimer(30)
{
    m_font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf");
}

void DialogSysTest::Process(sf::RenderWindow& rRenderWindow)
{
    mTimer = std::min(mTimer + 1, k_mMaxTimer);
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
    std::istringstream iss(k_testText);
    std::shared_ptr<DialogContainer> m_pDialogContainer;
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
            m_pDialogContainer->contentList = std::list<std::list<std::string>>({{""}});
            continue;
        }
        if (subs.front() == '|' && subs.back() == '|')
        {
            m_dialogContainerList.emplace_back(*m_pDialogContainer);
            break;
        }
        sf::Text testText(m_pDialogContainer->contentList.back().back() + std::string(subs), m_font, m_textHeight);
        int textActualWidth = testText.getLocalBounds().width;
        if (textActualWidth > m_maxWidthForText)
        {
            if (m_pDialogContainer->contentList.back().size() > 2)
            {
                m_pDialogContainer->contentList.push_back({""});
            }
            else
            {
                m_pDialogContainer->contentList.back().push_back("");
            }
        }
        m_pDialogContainer->contentList.back().back() += std::string(" ") + subs;
    }
    while (iss);
    std::cout << m_dialogContainerList.front().contentList.back().back() << std::endl;
    m_state = State_t::PRODUCING;
}

void DialogSysTest::ProcessProducing(sf::RenderWindow& rRenderWindow)
{

    if (m_dialogContainerList.empty())
    {
        m_state = State_t::FINISHED;
    }
    else
    {
        sf::RectangleShape rect(sf::Vector2f(1714.f, 174.f));
        rect.setFillColor(sf::Color::Blue);
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(3.f);
        rect.setPosition(sf::Vector2f(100.f, 903.f));
        rRenderWindow.draw(rect);

        sf::RectangleShape portraitRect(sf::Vector2f(280, 134.f));
        portraitRect.setPosition(sf::Vector2f(110.f, 923.f));
        portraitRect.setFillColor(m_dialogContainerList.front().portraitName == "person" ? sf::Color::Black : sf::Color::Magenta);
        rect.setOutlineColor(sf::Color::Cyan);
        rect.setOutlineThickness(3.f);

        rRenderWindow.draw(portraitRect);
        std::string firstThingToWrite = m_dialogContainerList.front().contentList.front().front();
        sf::Text text(firstThingToWrite, m_font, m_textHeight);
        text.setPosition(400.f, 903.f);
        rRenderWindow.draw(text);
        if (m_dialogContainerList.front().contentList.front().size() == 2 || m_dialogContainerList.front().contentList.front().size() == 3)
        {
            std::string nextThingToWrite = *std::next(m_dialogContainerList.front().contentList.front().begin());
            sf::Text text(nextThingToWrite, m_font, m_textHeight);
            text.setPosition(400.f, 953.f);
            rRenderWindow.draw(text);
        }
        if (m_dialogContainerList.front().contentList.front().size() == 3)
        {
            std::string nextThingToWrite = *std::next(std::next(m_dialogContainerList.front().contentList.front().begin()));
            sf::Text text(nextThingToWrite, m_font, m_textHeight);
            text.setPosition(400.f, 1003.f);
            rRenderWindow.draw(text);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mTimer == k_mMaxTimer)
    {
        mTimer = 0;
        if (!m_dialogContainerList.empty())
        {
            if (m_dialogContainerList.front().contentList.size() > 1)
            {
                m_dialogContainerList.front().contentList.pop_front();
            }
            else
            {
                m_dialogContainerList.pop_front();
            }
        }
    }
}

void DialogSysTest::ProcessFinished(sf::RenderWindow& rRenderWindow)
{
	std::cout << "Finished" << std::endl;
	m_state = State_t::WAITING;
}