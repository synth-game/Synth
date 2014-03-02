/*!
 * \file LevelSprite.h
 * \brief Sprite of the level with lights rendering
 * \author Jijidici
 * \date 26/02/2014
 */
#ifndef GAME_LEVEL_SPRITE_H
#define GAME_LEVEL_SPRITE_H

#include <vector>
#include "cocos2d.h"
#include "Core/SynthActor.h"

USING_NS_CC;

namespace game {

/* \brief Sprite of the level with lights rendering */
class LevelSprite : public Sprite {
public:
	/*! \brief Destructor */
	~LevelSprite();

	static LevelSprite* create(char* sBackgroundPath, core::SynthActor* pHero);
	void addLight(Texture2D* pTexture, Color4B color);
	void draw();


protected:
	struct LightTexture {
		Texture2D* pTex;
		std::vector<float> col;
	};

	/*! \brief Constructor */
	LevelSprite();

	Sprite* _pHeroSprite;
	std::vector<LightTexture*> _lightTextures;
};

}  // namespace game
#endif
