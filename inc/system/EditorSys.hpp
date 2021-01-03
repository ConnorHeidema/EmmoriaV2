#ifndef __EDITOR_SYS__
#define __EDITOR_SYS__

#include "system/System.hpp"
#include <entt/fwd.hpp>
#include <vector>

class Position;

namespace sf { class Mouse; }

class EditorSys
	: public System
{
public:
	EditorSys(std::string systemConfigItem, entt::registry& rReg);

private:
	void Update_() override;

	void GetNewScrollPosition_();
	int GetTextureSubIndex_();
	std::string GetSpriteName_();
	void DisableUnusefulSystems_();
	void UpdateSetOfOptions_();
	void CreateCursor_();
	void WriteTextureLineToTemp_(int textureIndex, Position const& pos);
	void WriteSpriteLineToTemp_(std::string spriteName);
	bool CheckIfTiledIndexExists_(std::string const& filepath, int xIndex, int yIndex);


	entt::registry& m_rReg;

	std::vector<std::string> m_thingsToPlaceDownSet;
	int m_currentSetIndex;
	bool m_bEditing;
};

#endif