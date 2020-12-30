#include "util/EntityLoaderUtils.hpp"

#include "util/ApplicationParameters.hpp"
#include "util/FontContainer.hpp"

#include <SFML/Graphics.hpp>

int EntityLoaderUtils::GetTextWidth(std::string text, int height)
{
	sf::Text dummyText;
	sf::Font font;
	font = *FontContainer::GetFont(ApplicationParameters::k_fontPath);
	dummyText.setFont(font);
	dummyText.setCharacterSize(height*ApplicationParameters::k_textFactor);
	dummyText.setString(text);
	return dummyText.getLocalBounds().width;
}