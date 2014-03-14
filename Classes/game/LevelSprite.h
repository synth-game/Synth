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

	static LevelSprite* create(const char* sBackgroundPath);
	void addLight(int actorID, Texture2D* pTexture, Color4B color);
	void updateLight(core::SynthActor* pLamp);
	void draw();

	/*! \brief  */
	void onChangeNodeOwner(EventCustom* pEvent);


protected:
	struct LightTexture {
		int actorID;
		Texture2D* pTex;
		std::vector<float> col;
	};

	/*! \brief Constructor */
	LevelSprite();

	std::vector<LightTexture*> _lightTextures;

};

}  // namespace game
#endif
