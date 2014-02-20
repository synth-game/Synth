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

#include "events/EditMoveEvent.h"

namespace graphics {

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent() {
}

HeroAnimatedSpriteComponent::HeroAnimatedSpriteComponent(Layer* pParent) : 
	AnimatedSpriteComponent(pParent) {
	
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

		_sState = "on_floor";
		_sCurrentAnimName = "walk";
		cocos2d::Animation* walkAnimation = graphicManager->getAnimation(_sCurrentAnimName, _pFrameCache);
		cocos2d::Animate* walkAnimate = cocos2d::Animate::create(walkAnimation);
		walkAnimate->retain();
		_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimate ));
	}
}

void HeroAnimatedSpriteComponent::initListeners() {
	_pEditMoveEventListener = cocos2d::EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onEditMove, this));
	// etc.. TODO
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent*	pEditMoveEvent	= static_cast<events::EditMoveEvent*>(pEvent);
    core::SynthActor*		pSource			= static_cast<core::SynthActor*>(pEditMoveEvent->getSource());
    core::SynthActor*		pOwner			= static_cast<core::SynthActor*>(_owner);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	cocos2d::Animation* walkAnimation = graphicManager->getAnimation(_sCurrentAnimName, _pFrameCache);
	cocos2d::Animate* walkAnimate = cocos2d::Animate::create(walkAnimation);

    if (pSource->getActorID() == pOwner->getActorID()) {
		if (pEditMoveEvent->isStartMoving()) {
			if (pEditMoveEvent->getDirection().x < 0) {
				_pSprite->setFlippedX(true);
				_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimate ));
			}
			else if(pEditMoveEvent->getDirection().x > 0) {
				_pSprite->setFlippedX(false);

				_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimate ));
			}
		} else {
			_pSprite->stopAllActions();
		}
    }
    else {
        CCLOG("MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
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
