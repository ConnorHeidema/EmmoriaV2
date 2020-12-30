#include "util/FontContainer.hpp"

#include <SFML/Graphics.hpp>

std::unordered_map<std::string, std::shared_ptr<sf::Font>> FontContainer::m_fontMap = {};

FontContainer::FontContainer()
{}

std::shared_ptr<sf::Font> FontContainer::GetFont(std::string const& fontName)
{
	auto potentialFontIter = m_fontMap.find(fontName);
	if (potentialFontIter == m_fontMap.end())
	{
		auto pFont = LoadFont_(fontName);
		m_fontMap.insert(std::pair<std::string, std::shared_ptr<sf::Font>>(fontName, pFont));
		return pFont;
	}
	return potentialFontIter->second;
}

std::shared_ptr<sf::Font> FontContainer::LoadFont_(std::string const& fontName)
{
	auto pPotentialFont = std::make_shared<sf::Font>();
	pPotentialFont->loadFromFile(fontName);
	return pPotentialFont;
}
