#ifndef __GAME_RENDER_SYS__
#define __GAME_RENDER_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>

namespace sf { class RenderWindow; }

class GameRenderSys
	: public System
{
public:
	GameRenderSys(std::string systemConfigItem, entt::registry& rReg, sf::RenderWindow& rRenderWindow);

private:
	void Update_() override;
	void RenderHealth_();
	void ResetRenderState_();
	void RenderTileMapPieces_();
	void RenderRotatableSprites_();
	void RenderBasicSprites_();
	void RenderDialog_();
	void RenderText_();

	void RenderHealthBar_(
		float const& spriteWidth,
		float const& xPosition,
		float const& yPosition,
		float const& healthRatio);

	entt::registry& m_rReg;
	sf::RenderWindow& m_rRenderWindow;
};

#endif