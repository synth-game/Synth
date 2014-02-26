/*!
 * \file LevelSprite.cpp
 * \brief Sprite of the level with lights rendering
 * \author Jijidici
 * \date 26/02/2014
 */
#include "LevelSprite.h"
#include "game/SHA_level_sprite.h"

#define LIGHT_MAX_COUNT 16

namespace game {

LevelSprite::LevelSprite() {
}

LevelSprite::~LevelSprite() {
	for(std::vector<LightTexture*>::iterator it=_lightTextures.begin(); it!=_lightTextures.end(); ++it) {
		delete *it;
		*it = nullptr;
	}
	_lightTextures.clear();
}

LevelSprite* LevelSprite::create(char* sBackgroundPath) {
	LevelSprite* pRet = new LevelSprite();
	if (pRet != nullptr && pRet->initWithFile(sBackgroundPath)) {
		CCLOG("LevelSprite created");
		pRet->autorelease();
		pRet->setAnchorPoint(Point::ZERO);

		GLProgram* pProgram = new GLProgram();
		pProgram->initWithVertexShaderByteArray(levelSprite_vert, levelSprite_frag);
		pProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		pProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		pProgram->link();
		pProgram->updateUniforms();
		pProgram->use();
		pRet->setShaderProgram(pProgram);

	} else {
		CCLOG("LevelSprite created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void LevelSprite::addLight(Texture2D* pTexture, Color4F color, bool bOn) {
	if (_lightTextures.size() < LIGHT_MAX_COUNT) {
		LightTexture* pLT = new LightTexture();
		pLT->pTex = pTexture;
		pLT->col.push_back(color.r);
		pLT->col.push_back(color.g);
		pLT->col.push_back(color.b);
		pLT->bIsOn = bOn;
		_lightTextures.push_back(pLT);
	} else {
		CCLOG("There already are maximum of lights in LevelSprite. Can't add another one.");
	}
}

void LevelSprite::draw() {
	Sprite::draw();
}

}  // namespace game
