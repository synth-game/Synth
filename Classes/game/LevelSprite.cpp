/*!
 * \file LevelSprite.cpp
 * \brief Sprite of the level with lights rendering
 * \author Jijidici
 * \date 26/02/2014
 */
#include <sstream>
#include "LevelSprite.h"
#include "game/SHA_level_sprite.h"
#include "graphics/SpriteComponent.h"

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

LevelSprite* LevelSprite::create(const char* sBackgroundPath) {
	LevelSprite* pRet = new LevelSprite();
	if (pRet != nullptr && pRet->initWithFile(sBackgroundPath)) {
		CCLOG("LevelSprite::create : LevelSprite created");
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

void LevelSprite::addLight(Texture2D* pTexture, Color4B color) {
	if (_lightTextures.size() < SHA_LIGHT_MAX_COUNT) {
		LightTexture* pLT = new LightTexture();
		pLT->pTex = pTexture;
		pLT->col.push_back(static_cast<float>(color.r)/255.f);
		pLT->col.push_back(static_cast<float>(color.g)/255.f);
		pLT->col.push_back(static_cast<float>(color.b)/255.f);
		pLT->col.push_back(static_cast<float>(color.a)/255.f);
		_lightTextures.push_back(pLT);
	} else {
		CCLOG("There already are maximum of lights in LevelSprite. Can't add another one.");
	}
}

void LevelSprite::draw() {
	_shaderProgram->use();
	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_LevelPixelSize"), 1.f/_contentSize.width, 1.f/_contentSize.height);
	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_LightCount"), _lightTextures.size());
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		std::stringstream lightLocation;
		lightLocation << "SY_Lights_" << i;
		_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName(lightLocation.str().c_str()), i+2);

		std::stringstream colorLocation;
		colorLocation << "SY_Colors["<<i<<"]";
		_shaderProgram->setUniformLocationWith4fv(_shaderProgram->getUniformLocationForName(colorLocation.str().c_str()), &(_lightTextures[i]->col[0]), 1);

		GL::bindTexture2DN(i+1, _lightTextures[i]->pTex->getName());
	}

	Sprite::draw();

	GL::bindTexture2DN(1, 0);
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		GL::bindTexture2DN(i+1, 0);
	}
}

}  // namespace game
