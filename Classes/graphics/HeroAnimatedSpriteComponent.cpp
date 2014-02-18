/*!
 * \file HeroAnimatedSpriteComponent.cpp
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#include "HeroAnimatedSpriteComponent.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"
#include "core/SynthActor.h"

namespace graphics {

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent() {
}

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent(Layer* pParent) : 
	AnimatedSpriteComponent() {
	_pParent = pParent;
	_pSprite = nullptr;
	_pFrameCache = nullptr;
	_pBatchNode = nullptr;
}

HeroAnimatedSpriteComponent::~HeroAnimatedSpriteComponent() {
}

bool HeroAnimatedSpriteComponent::init() {
    SynthComponent::init(HeroAnimatedSpriteComponent::COMPONENT_TYPE);
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

	GraphicManager* graphicManager = GraphicManager::getInstance();
	std::string actorTag = static_cast<core::SynthActor*>(_owner)->getActorTag();
	_pBatchNode = graphicManager->getBatchNode(actorTag);
	_pFrameCache = graphicManager->getFrameCache(actorTag);

	if(_pBatchNode != nullptr && _pFrameCache != nullptr) {
		// position
		_pBatchNode->setPosition(geometryComponent->getPosition());

		// animation
		_pSprite = cocos2d::Sprite::createWithSpriteFrameName("walk_0.png");
		_pBatchNode->addChild(_pSprite);

		_pParent->addChild(_pBatchNode, 1, 3);

		cocos2d::Animation* walkAnimation = graphicManager->getAnimation("walk", _pFrameCache);
		
		cocos2d::Animate* walkAnimate = cocos2d::Animate::create(walkAnimation);
		walkAnimate->retain();

		_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimate ));
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
