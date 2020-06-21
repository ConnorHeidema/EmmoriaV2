#include "system/DialogSys.hpp"

#include "component/PositionComp.hpp"
#include "component/SizeComp.hpp"
#include "component/RenderableComp.hpp"
#include "component/RenderableTextComp.hpp"
#include "component/ClickableComp.hpp"

#include "util/ApplicationParameters.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

void DialogSys::Update(entt::registry& reg, std::shared_ptr<sf::RenderWindow> pRenderWindow)
{
	reg.view<
		PositionComp,
		SizeComp,
		ClickableComp,
		RenderableComp,
		RenderableTextComp
		>().each([&](auto entity, auto &posComp, auto& sizeComp, auto& stringText) {
		sf::RectangleShape rectShape(sf::Vector2f(sizeComp.size.width,sizeComp.size.height));
		rectShape.setPosition(sf::Vector2f(posComp.position.x, posComp.position.y));
		rectShape.setFillColor(sf::Color::Green);
		pRenderWindow->draw(rectShape);
		sf::Text text;
		sf::Font font;
		font.loadFromFile(ApplicationParameters::k_fontPath);
		text.setFont(font);
		text.setPosition(sf::Vector2f(posComp.position.x, posComp.position.y));
		text.setCharacterSize(sizeComp.size.height);
		text.setString(stringText.m_text);
		pRenderWindow->draw(text);
	});
}