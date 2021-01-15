#include "system/LightSys.hpp"

#include "ltbl/lighting/LightShape.h"
#include "ltbl/lighting/LightSystem.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

struct LightSys::Impl 
{
	Impl(entt::registry& rReg, sf::RenderWindow& rRenderWindow)
		: m_rReg(rReg)
		, m_rRenderWindow(rRenderWindow)
		, m_unshadowShader()
		, m_lightOverShapeShader()
		, m_penumbraTexture()
	{ 
		m_unshadowShader.loadFromFile("sprite/light/unshadowShader.vert", "sprite/light/unshadowShader.frag");
		m_lightOverShapeShader.loadFromFile("sprite/light/lightOverShapeShader.vert", "sprite/light/lightOverShapeShader.frag");
		m_penumbraTexture.loadFromFile("sprite/light/penumbraTexture.png");
		m_penumbraTexture.setSmooth(true);
	}
	~Impl() {};

	void Update();

	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
	sf::Shader m_unshadowShader;
	sf::Shader m_lightOverShapeShader;
	sf::Texture m_penumbraTexture;
};

void LightSys::Impl::Update()
{
	ltbl::LightSystem ls;
	ls.create(sf::FloatRect(-1000.0f, -1000.0f, 1000.0f, 1000.0f), m_rRenderWindow.getSize(), m_penumbraTexture, m_unshadowShader, m_lightOverShapeShader);
}

LightSys::LightSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow)
	: System(systemConfigItem)
	, pImpl(std::make_unique<Impl>(rReg, rRenderWindow)) 
{
}

void LightSys::Update_()
{
	pImpl->Update();
}
