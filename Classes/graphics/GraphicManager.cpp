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
		_pInstance->init();
    }
	return _pInstance;
}

void GraphicManager::init(/*core::xml data*/) {

	// framecache
	_pFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	_pFrameCache->addSpriteFramesWithFile("sprites/girl.plist");
	_pFrameCache->retain();

	// batchnode
	_pBatchNode = SpriteBatchNode::create("sprites/girl.pvr");

	// parsing animations
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile("xml/animations.xml");
	if(xmlerror == 0) {
		CCLOG("NO ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmlerror);
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pAnimationData, *pFrameData;
		std::string type, name = "";
		Animation* pAnimation;
		std::vector<std::string> aFrames;
		int i = 0; 
		int j = 0;

		pAnimationData = pXMLFile->FirstChildElement("animation");
		while(pAnimationData)
		{	
			type = pAnimationData->Attribute("type");
			CCLOG("ANIMATION n°%d, type: %s ,PARSED !", ++i, type.c_str());
			pFrameData = pAnimationData->FirstChildElement("frame");
			while(pFrameData) {
				name = pFrameData->Attribute("name");
				aFrames.push_back(name);
				CCLOG("FRAME n°%d, name: %s, PARSED !", ++j, name.c_str());
				pFrameData = pFrameData->NextSiblingElement("frame");
			}
			pAnimation = __createAnimation(aFrames);
			_animations.insert(std::pair<AnimationType, Animation*>(AnimationType::HERO_WALK, pAnimation));
			pAnimationData = pAnimationData->NextSiblingElement("animation");
		}
	} else {
		CCLOG("ERROR WHILE LOADING XML FILE !!!!!!!!! : %d", xmlerror);
	}
}

Sprite* GraphicManager::createSprite(std::string sSpriteName) {
	Sprite* pSprite = Sprite::create(sSpriteName.c_str());
	pSprite->setAnchorPoint(Point(0.f, 1.f));
	pSprite->setPosition(Point(0.f, pSprite->getContentSize().height));
	return pSprite;
}

Animation* GraphicManager::__createAnimation(std::vector<std::string> aFrames) {
	cocos2d::Array* animFrames = cocos2d::Array::create();
	for(int i = 0; i < aFrames.size(); i++) {
		cocos2d::SpriteFrame* frame = _pFrameCache->spriteFrameByName( aFrames[i].c_str() );
		frame->retain();
		animFrames->addObject(frame);
	}
	Animation* pAnimation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	pAnimation->retain();
	return pAnimation;
}

Animation* GraphicManager::getAnimation(AnimationType eAnimationType) {
	std::map<AnimationType,Animation*>::iterator it = _animations.find(eAnimationType);
	Animation* pRes = it->second;	
	return pRes;
}

Animation* GraphicManager::getNextAnimation(AnimationType eAnimationType) {
	return 0;
}

bool GraphicManager::isLoopAnimation(std::string sAnimName) {
	return 0;
}


}  // namespace graphics
