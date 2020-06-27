#include "system/DialogSys.hpp"

#include "component/PositionComp.hpp"
#include "component/SizeComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/RenderableTextComp.hpp"
#include "component/functional/ClickableComp.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/MouseUtils.hpp"
#include "util/Helper.hpp"

#include <entt/entt.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

DialogSys::DialogSys(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: m_rRenderWindow(rRenderWindow)
	, m_rReg(rReg)
	, m_dialogSysState(WAITING)
	, m_curClickFrame(0)
{}

void DialogSys::Update()
{
	switch (m_dialogSysState)
	{
		case WAITING: WaitingUpdate_(); break;
		case CONSUMING: ConsumingUpdate_(); break;
		case PRESENTING: PresentingUpdate_(); break;
	}
}

void DialogSys::WaitingUpdate_()
{
	bool bDialogFound = false;
	m_rReg.view<
		SizeComp,
		RenderableComp,
		RenderableTextComp,
		PositionComp,
		ClickableComp
		>
	().each([&](auto entity, auto& sizeComp, auto& stringText, auto& posComp, auto& clickableComp)
	{
		m_curPosition.x = Helper::Rand(1, ApplicationParameters::k_screenWidth - 400);
		m_curPosition.y = Helper::Rand(1, ApplicationParameters::k_screenHeight - 150);

		m_curSize = sizeComp.size;
		DelimitText_(stringText.m_text);

		m_rReg.destroy(entity);
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

void DialogSys::PresentingUpdate_()
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
		m_rRenderWindow.draw(rectShape);
		m_rRenderWindow.draw(text);

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
