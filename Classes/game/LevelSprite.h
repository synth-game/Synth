#ifndef GAME_LEVEL_SPRITE_H
#define GAME_LEVEL_SPRITE_H

#include <vector>
#include "cocos2d.h"
#include "Game/LightTexture.h"
#include "Core/SynthActor.h"

USING_NS_CC;

namespace game
{
class LevelSprite : public Sprite
{
private:
	std::vector<LightTexture> _lightTexturesWithOcclusion;

	std::vector<LightTexture> _lightTexturesWithoutOcclusion;


protected:
	LevelSprite();

public:
	~LevelSprite();

	/**
	 * Load the background sprite and the Texture2D from the GraphicManager
	 */
	static LevelSprite* create(char* sSpriteName);

	void updateLights(std::vector<core::SynthActor*> lights);

	/**
	 * redéfinition
	 */
	void draw();

};

}  // namespace game
#endif
