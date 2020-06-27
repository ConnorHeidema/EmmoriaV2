#include "entity/EntityLoaderFactory.hpp"

#include "util/ApplicationParameters.hpp"

#include "component/tag/ButtonComp.hpp"

#include "component/functional/RenderableComp.hpp"
#include "component/functional/PositionComp.hpp"
#include "component/functional/SizeComp.hpp"
#include "component/functional/TextComp.hpp"
#include "component/functional/ClickableComp.hpp"
#include "component/functional/SpriteComp.hpp"

#include <SFML/Graphics.hpp>

#include <string>

void EntityLoaderFactory::LoadFile(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();

	rReg.emplace<ButtonComp>(entity);

	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
	renderableComp.m_bRendered = false;

	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	auto& positionComp = rReg.emplace<PositionComp>(entity);
	rReg.emplace<ClickableComp>(entity);

	std::string token;
	reader >> token;
	positionComp.m_position.x = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	positionComp.m_position.y = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

	auto& textComp = rReg.emplace<TextComp>(entity);
	reader >> token;

	replace( token.begin(), token.end(), '_', ' ');
	textComp.m_text = token;

	sf::Text dummyText;
	sf::Font font;
	font.loadFromFile(ApplicationParameters::k_fontPath);
	dummyText.setFont(font);
	dummyText.setCharacterSize(sizeComp.m_size.height*ApplicationParameters::k_textFactor);
	dummyText.setString(textComp.m_text);

	sizeComp.m_size.width = dummyText.getLocalBounds().width;
}

void EntityLoaderFactory::LoadBackground(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();
	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
	renderableComp.m_bRendered = false;

	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	sizeComp.m_size.width = ApplicationParameters::k_screenWidth;
	sizeComp.m_size.height = ApplicationParameters::k_screenHeight;

	auto& positionComp = rReg.emplace<PositionComp>(entity);
	positionComp.m_position.x = 50 * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	positionComp.m_position.y = 50 * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;

	auto& spriteComp = rReg.emplace<SpriteComp>(entity);
	std::string token;
	reader >> token;
	spriteComp.m_filePath = ApplicationParameters::k_spritePath + token + ".png";
}

void EntityLoaderFactory::LoadRandomDialog(entt::registry& rReg, std::istringstream& reader)
{
	auto entity = rReg.create();
	auto& sizeComp = rReg.emplace<SizeComp>(entity);
	auto& textComp = rReg.emplace<TextComp>(entity);
	rReg.emplace<PositionComp>(entity);
	rReg.emplace<ClickableComp>(entity);

	auto& renderableComp = rReg.emplace<RenderableComp>(entity);
	renderableComp.m_bRendered = false;

	std::string token;
	reader >> token;
	sizeComp.m_size.width = std::stoi(token) * ApplicationParameters::k_screenWidth / ApplicationParameters::k_widthUnits;
	reader >> token;
	sizeComp.m_size.height = std::stoi(token) * ApplicationParameters::k_screenHeight / ApplicationParameters::k_heightUnits;
	while (reader >> token) { textComp.m_text += token + " "; }
}
