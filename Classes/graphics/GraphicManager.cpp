/*!
 * \file GraphicManager.h
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 * \author Chupee
 * \date 12/02/2014
 */
#include "GraphicManager.h"

namespace graphics {

GraphicManager* GraphicManager::_pInstance = nullptr;

GraphicManager::GraphicManager() {
}

GraphicManager::~GraphicManager() {
}

GraphicManager* GraphicManager::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new GraphicManager();
    }
	return _pInstance;
}

void GraphicManager::init(core::xml data) {
}

Sprite* GraphicManager::createSprite(std::string sSpriteName) {
	Sprite* pSprite = Sprite::create(sSpriteName.c_str());
	pSprite->setAnchorPoint(Point(0.f, 1.f));
	pSprite->setPosition(Point(0.f, pSprite->getContentSize().height));
	return pSprite;
}

Animation* GraphicManager::getAnimation(std::string sAnimName, SpriteFrameCache* pFrameCache) {
	cocos2d::Array* animFrames = cocos2d::Array::create();
	char str[100] = {0};
	for(int i = 1; i <= 7; i++) {
		sprintf(str, "%s_%d.png", sAnimName.c_str(), i);
		cocos2d::SpriteFrame* frame = pFrameCache->spriteFrameByName( str );
		frame->retain();
		animFrames->addObject(frame);
	}
	return cocos2d::Animation::createWithSpriteFrames(animFrames, 0.1f);
}

Animation* GraphicManager::getNextAnimation(std::string sAnimName) {
	return 0;
}

SpriteBatchNode* GraphicManager::getBatchNode(std::string sActorName) {
	std::string sPvrFile = "";
	if(sActorName == "HERO") {
		sPvrFile = "sprites/girl.pvr";
	} else if(sActorName == "FIREFLY") {
		sPvrFile = "";
	}
	SpriteBatchNode* pBatchNode = nullptr;
	if(sPvrFile != "") {
		pBatchNode = SpriteBatchNode::create(sPvrFile.c_str());
	} 
	return pBatchNode;
}

SpriteFrameCache* GraphicManager::getFrameCache(std::string sActorName) {
	std::string sPlistFile = "";
	if(sActorName == "HERO") {
		sPlistFile = "sprites/girl.plist";
	} else if(sActorName == "FIREFLY") {
		sPlistFile = "";
	}

	SpriteFrameCache* pFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	pFrameCache->addSpriteFramesWithFile(sPlistFile.c_str());
	pFrameCache->retain();

	return pFrameCache;
}

bool GraphicManager::isLoopAnimation(std::string sAnimName) {
	return 0;
}


}  // namespace graphics
