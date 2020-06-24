#include "system/DialogSys.hpp"

#include "component/PositionComp.hpp"
#include "component/SizeComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/RenderableTextComp.hpp"
#include "component/ClickableComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/MouseUtils.hpp"
#include "util/Helper.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>


DialogSys::DialogSys() : m_dialogSysState(WAITING), m_curClickFrame(0)
{}

void DialogSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	switch (m_dialogSysState)
	{
		case WAITING: WaitingUpdate_(reg); break;
		case CONSUMING: ConsumingUpdate_(); break;
		case PRESENTING: PresentingUpdate_(pRenderWindow); break;
	}
}

void DialogSys::WaitingUpdate_(entt::registry& reg)
{
	bool bDialogFound = false;
	reg.view<
		SizeComp,
		ClickableComp,
		RenderableComp,
		RenderableTextComp,
		PositionComp
		>
	().each([&](auto entity, auto& sizeComp, auto& stringText, auto& posComp)
	{
		m_curPosition.x = Helper::Rand(1, ApplicationParameters::k_screenWidth - 400);
		m_curPosition.y = Helper::Rand(1, ApplicationParameters::k_screenHeight - 150);

		m_curSize = sizeComp.size;
		DelimitText_(stringText.m_text);

		reg.destroy(entity);
		bDialogFound = true;
	});

	m_dialogSysState = (bDialogFound ? PRESENTING : WAITING);
}

void DialogSys::ConsumingUpdate_()
{
	m_curPosition.x = Helper::Rand(1, ApplicationParameters::k_screenWidth - 400);
	m_curPosition.y = Helper::Rand(1, ApplicationParameters::k_screenHeight - 150);
	m_currentDialogList.remove(m_currentDialogList.front());
	m_curClickFrame++;
	m_dialogSysState = (m_currentDialogList.empty() ? WAITING : PRESENTING);
}

void DialogSys::PresentingUpdate_(std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
		if (m_curClickFrame > 0 &&
			m_curClickFrame < ApplicationParameters::k_debounceFrames)
		{ m_curClickFrame++; }

		if (m_curClickFrame == ApplicationParameters::k_debounceFrames) { m_curClickFrame = 0; }

		sf::Text text;
		sf::Font font;
		font.loadFromFile(ApplicationParameters::k_fontPath);
		text.setFont(font);
		text.setPosition(sf::Vector2f(m_curPosition.x, m_curPosition.y));
		text.setCharacterSize(m_curSize.height);
		text.setString(m_currentDialogList.front());

		sf::RectangleShape rectShape(sf::Vector2f(text.getLocalBounds().width, m_curSize.height * 1.5));
		rectShape.setPosition(sf::Vector2f(m_curPosition.x, m_curPosition.y));
		rectShape.setFillColor(sf::Color::Green);
		pRenderWindow->draw(rectShape);
		pRenderWindow->draw(text);

		m_dialogSysState = (
			MouseUtils::IsCollisionDetected_(
				m_curPosition.x,
				m_curPosition.y,
				m_curSize.width,
				m_curSize.height * 1.5,
				sf::Mouse::getPosition().x,
				sf::Mouse::getPosition().y) &&
				sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				m_curClickFrame == 0 ?
					CONSUMING :
					PRESENTING);
}

void DialogSys::DelimitText_(std::string& text)
{
	std::string const& delimiter = ApplicationParameters::k_dialogDelimiter;
	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		m_currentDialogList.emplace_back(text.substr(0, pos));
		text.erase(0, pos + delimiter.length());
	}
	m_currentDialogList.emplace_back(text.substr(0, pos));
}
