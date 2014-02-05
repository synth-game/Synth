#ifndef GAME_LIGHT_TEXTURE_H
#define GAME_LIGHT_TEXTURE_H

#include "cocos2d.h"

USING_NS_CC;

namespace game
{
/**
 * Intern class of LevelSprite
 */
class LightTexture
{
public:
	int iID;

	Texture2D* pTexture;

	Color4B color;

};

}  // namespace game
#endif
