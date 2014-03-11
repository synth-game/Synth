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

LevelSprite::LevelSprite() 
	: _pHeroSprite(nullptr) {
}

LevelSprite::~LevelSprite() {
	for(std::vector<LightTexture*>::iterator it=_lightTextures.begin(); it!=_lightTextures.end(); ++it) {
		delete *it;
		*it = nullptr;
	}
	_lightTextures.clear();
}

LevelSprite* LevelSprite::create(const char* sBackgroundPath, core::SynthActor* pHero) {
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

		//get the hero sprite
		graphics::SpriteComponent* pSpriteComp = static_cast<graphics::SpriteComponent*>(pHero->getComponent(graphics::SpriteComponent::COMPONENT_TYPE));
		CCASSERT(pSpriteComp != nullptr, "LevelSprite needs a SynthActor (the hero) with a SpriteComponent");
		pRet->_pHeroSprite = pSpriteComp->getSprite();

	} else {
		CCLOG("LevelSprite created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void LevelSprite::addLight(Texture2D* pTexture, Point position, Color4B color) {
	if (_lightTextures.size() < SHA_LIGHT_MAX_COUNT) {
		LightTexture* pLT = new LightTexture();
		pLT->pTex = pTexture;
		pLT->pos.push_back(position.x);
		pLT->pos.push_back(position.y);
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
	
	//construct sprite frame texture rectangle - because the frame texture is the entire spreadsheet
	SpriteFrame* pCurrentFrame = _pHeroSprite->getDisplayFrame();
	Size entireTexSize = _pHeroSprite->getTexture()->getContentSizeInPixels();
	Rect frameRectPix = pCurrentFrame->getRectInPixels();
	Rect frameRect = Rect(frameRectPix.origin.x/entireTexSize.width, frameRectPix.origin.y/entireTexSize.height, frameRectPix.size.width/entireTexSize.width, frameRectPix.size.height/entireTexSize.height);
	Point heroPos = Point(_pHeroSprite->getPosition().x-frameRectPix.size.width/2.f + pCurrentFrame->getOffsetInPixels().x, _contentSize.height - (_pHeroSprite->getPosition().y+frameRectPix.size.height/2.f + pCurrentFrame->getOffsetInPixels().y));
	int iIsFrameRotated = 0;
	int iIsFrameFlippedX = 0;
	if(pCurrentFrame->isRotated()){ iIsFrameRotated = 1; }
	if(_pHeroSprite->isFlippedX()){
		iIsFrameFlippedX = 1;
		heroPos.x -=  2.*pCurrentFrame->getOffsetInPixels().x;
	}

	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_HeroPixelSize"), 1.f/frameRectPix.size.width, 1.f/frameRectPix.size.height);
	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_HeroPos"), heroPos.x, heroPos.y);
	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_HeroTex"), 1);
	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_HeroTexPos"), frameRect.origin.x, frameRect.origin.y);
	_shaderProgram->setUniformLocationWith2f(_shaderProgram->getUniformLocationForName("SY_HeroTexSize"), frameRect.size.width, frameRect.size.height);
	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_HeroIsRotated"), iIsFrameRotated);
	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_HeroIsFlippedX"), iIsFrameFlippedX);
	GL::bindTexture2DN(1, _pHeroSprite->getTexture()->getName());

	_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName("SY_LightCount"), _lightTextures.size());
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		std::stringstream lightLocation;
		lightLocation << "SY_Lights_" << i;
		_shaderProgram->setUniformLocationWith1i(_shaderProgram->getUniformLocationForName(lightLocation.str().c_str()), i+2);

		std::stringstream posLocation;
		posLocation << "SY_LightPos["<<i<<"]";
		_shaderProgram->setUniformLocationWith2fv(_shaderProgram->getUniformLocationForName(posLocation.str().c_str()), &(_lightTextures[i]->pos[0]), 1);

		std::stringstream colorLocation;
		colorLocation << "SY_Colors["<<i<<"]";
		_shaderProgram->setUniformLocationWith4fv(_shaderProgram->getUniformLocationForName(colorLocation.str().c_str()), &(_lightTextures[i]->col[0]), 1);

		GL::bindTexture2DN(i+2, _lightTextures[i]->pTex->getName());
	}

	Sprite::draw();

	// Win rectangle
	DrawPrimitives::drawRect(Point(1050, 100), Point(1150, 300));

	GL::bindTexture2DN(1, 0);
	for(unsigned int i=0; i<_lightTextures.size(); ++i) {
		GL::bindTexture2DN(i+2, 0);
	}
}

}  // namespace game
