/*!
 * \file GraphicManager.h
 * \brief Singleton dealing with the graphics of the game (sprites, images)
 * \author Chupee
 * \date 12/02/2014
 */
#include "GraphicManager.h"
#include "system/IOManager.h"

namespace graphics {

GraphicManager* GraphicManager::_pInstance = nullptr;

GraphicManager::GraphicManager() :
	_pFrameCache(nullptr),
	_pBatchNode(nullptr) {
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

void GraphicManager::init() {

	// framecache
	_pFrameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
	_pFrameCache->addSpriteFramesWithFile("sprites/actors.plist");
	_pFrameCache->retain();

	// invert enum animation type
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_IDLE",			AnimationType::HERO_IDLE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_START_IDLE",		AnimationType::HERO_START_IDLE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_WALK",			AnimationType::HERO_WALK	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_STOP_WALK",		AnimationType::HERO_STOP_WALK	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_START_JUMP",		AnimationType::HERO_START_JUMP	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_JUMP",			AnimationType::HERO_JUMP	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_DURING_JUMP",		AnimationType::HERO_DURING_JUMP	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_FALL",			AnimationType::HERO_FALL	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_START_BOUNCE",	AnimationType::HERO_START_BOUNCE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_BOUNCE",			AnimationType::HERO_BOUNCE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_STOP_BOUNCE",		AnimationType::HERO_STOP_BOUNCE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_START_CRAWL",		AnimationType::HERO_START_CRAWL	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_CRAWL",			AnimationType::HERO_CRAWL	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_STOP_CRAWL",		AnimationType::HERO_STOP_CRAWL	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_IDLE_CRAWL",		AnimationType::HERO_IDLE_CRAWL	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_FLY",				AnimationType::HERO_FLY	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_HIT",				AnimationType::HERO_HIT	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_INTERACT",		AnimationType::HERO_INTERACT	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_COUGH",			AnimationType::HERO_COUGH	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_DIE",				AnimationType::HERO_DIE	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_WIN",				AnimationType::HERO_WIN	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"HERO_SPAWN",			AnimationType::HERO_SPAWN	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"BLUE_FIREFLY",			AnimationType::BLUE_FIREFLY	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"RED_FIREFLY",			AnimationType::RED_FIREFLY	));
	_tagsMap.insert(std::pair<std::string, AnimationType>(	"GREEN_FIREFLY",		AnimationType::GREEN_FIREFLY	));

	// parsing animations
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	synthsystem::IOManager* ioManager = synthsystem::IOManager::getInstance();
	pXMLFile = ioManager->loadXML("xml/animations.xml");
	if(pXMLFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pAnimationData, *pFrameData;
		std::string type, nextType, name, sIsLoop = "";
		bool bIsLoop = false;
		core::SynthAnimation* pAnimation;
		std::vector<std::string> aFrames;
		int i = 0;
		int j = 0;

		pAnimationData = pXMLFile->FirstChildElement("animation");
		while(pAnimationData)
		{
			aFrames.clear();
			bIsLoop = false;
			type = pAnimationData->Attribute("type");
			nextType = pAnimationData->Attribute("next");
			sIsLoop = pAnimationData->Attribute("isLoop");
			//CCLOG("ANIMATION n°%d, type: %s ,PARSED !", ++i, type.c_str());
			pFrameData = pAnimationData->FirstChildElement("frame");
			while (pFrameData) {
				name = pFrameData->Attribute("name");
				aFrames.push_back(name);
				pFrameData = pFrameData->NextSiblingElement("frame");
			}
			if ( sIsLoop == "true") {
				bIsLoop = true;
			}
			if (nextType.empty()) {
				pAnimation = new core::SynthAnimation(__getAnimationType(type), __createAnimation(aFrames), bIsLoop);
			} else {
				//CCLOG("ANIMATION NEXT ATTRIBUTE : %s", pAnimationData->Attribute("next"));
				pAnimation = new core::SynthAnimation(__getAnimationType(type), __getAnimationType(nextType), __createAnimation(aFrames), bIsLoop);
			}
			_animations.insert(std::pair<AnimationType, core::SynthAnimation*>(__getAnimationType(type), pAnimation));
	 		pAnimationData = pAnimationData->NextSiblingElement("animation");
		}
	}
}

Sprite* GraphicManager::createSprite(std::string sSpriteName) {
	Sprite* pSprite = Sprite::create(sSpriteName.c_str());
	pSprite->setAnchorPoint(Point(0.f, 1.f));
	pSprite->setPosition(Point(0.f, pSprite->getContentSize().height));
	return pSprite;
}

core::SynthAnimation* GraphicManager::getAnimation(AnimationType eAnimationType) {
	std::map<AnimationType,core::SynthAnimation*>::iterator it = _animations.find(eAnimationType);
	core::SynthAnimation* pRes = it->second;
	return pRes;
}

SpriteBatchNode* GraphicManager::getBatchNode() {
	if(_pBatchNode == nullptr) {
		_pBatchNode = SpriteBatchNode::create("sprites/actors.pvr");
	}
	return _pBatchNode;
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

AnimationType GraphicManager::__getAnimationType(std::string sTag) {
	return _tagsMap.find(sTag)->second;
}




}  // namespace graphics
