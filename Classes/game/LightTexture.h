#ifndef GAME_LIGHT_TEXTURE_H
#define GAME_LIGHT_TEXTURE_H

#include "Texture2D.h"
#include "Color4B.h"

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
