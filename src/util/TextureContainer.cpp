#include "util/TextureContainer.hpp"

#include <SFML/Graphics.hpp>

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureContainer::m_textureMap = {};

TextureContainer::TextureContainer()
{}

std::shared_ptr<sf::Texture> TextureContainer::GetTexture(std::string const& textureName)
{
	auto potentialTextureIter = m_textureMap.find(textureName);
	if (potentialTextureIter == m_textureMap.end())
	{
		auto pTexture = LoadTexture_(textureName);
		m_textureMap.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(textureName, pTexture));
		return pTexture;
	}
	return potentialTextureIter->second;
}

std::shared_ptr<sf::Texture> TextureContainer::LoadTexture_(std::string const& textureName)
{
	auto pPotentialTexture = std::make_shared<sf::Texture>();
	pPotentialTexture->loadFromFile(textureName);
	return pPotentialTexture;
}
