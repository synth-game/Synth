/*!
 * \file HeroAnimatedSpriteComponent.cpp
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#include "HeroAnimatedSpriteComponent.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"

namespace graphics {

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent() {
}

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent(Layer* pParent) : 
	AnimatedSpriteComponent() {
	_pParent = pParent;
	_pSprite = nullptr;
}

HeroAnimatedSpriteComponent::~HeroAnimatedSpriteComponent() {
}

bool HeroAnimatedSpriteComponent::init() {
    SynthComponent::init(HeroAnimatedSpriteComponent::COMPONENT_TYPE);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	_pBatchNode = SpriteBatchNode::create("sprites/girl.pvr");
	if(_pBatchNode != NULL) {
		SpriteFrameCache* frameCache = cocos2d::SpriteFrameCache::sharedSpriteFrameCache();
		frameCache->addSpriteFramesWithFile("sprites/girl.plist");
		frameCache->retain();

		_pSprite = cocos2d::Sprite::createWithSpriteFrameName("walk_0.png");
		_pBatchNode->addChild(_pSprite);
		_pBatchNode->setPosition(cocos2d::Point(0.f, 0.f));

		_pParent->addChild(_pBatchNode, 1, 3);

		// Sprite animation
		cocos2d::Array* animFrames = cocos2d::Array::create();
		char str[100] = {0};
		for(int i = 1; i <= 7; i++)
		{
			sprintf(str, "walk_%d.png", i);
			cocos2d::SpriteFrame* frame = frameCache->spriteFrameByName( str );
			frame->retain();
			animFrames->addObject(frame);
		}
		cocos2d::Animate* walkAnimation = cocos2d::Animate::create(cocos2d::Animation::createWithSpriteFrames(animFrames, 0.1f));
		walkAnimation->retain();

		_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimation ));

	}


	//Animation* anim = graphicManager->getAnimation("HERO_WALK");

	initListeners();
	return true;
}

HeroAnimatedSpriteComponent* HeroAnimatedSpriteComponent::create(Layer* pParent) {
	HeroAnimatedSpriteComponent* pRet = new HeroAnimatedSpriteComponent(pParent);
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void HeroAnimatedSpriteComponent::onEnter() {
	physics::GeometryComponent* geometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(geometryComponent != NULL, "HeroAnimatedSpriteComponent need a GeometryComponent added to its owner");
	if(_pBatchNode!= nullptr) {
		_pBatchNode->setPosition(geometryComponent->getPosition());
	}
}

void HeroAnimatedSpriteComponent::initListeners() {
	//_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onEditMove, this));
	// etc.. TODO
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onJump(EventCustom* pEvent) {

}

void HeroAnimatedSpriteComponent::onInterruptMove(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onToggleLight(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onDeath(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onWin(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onResetLevel(EventCustom* pEvent) {
}

}  // namespace graphics
