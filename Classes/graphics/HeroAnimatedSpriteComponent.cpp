/*!
 * \file HeroAnimatedSpriteComponent.cpp
 * \brief Gives an animated sprite to a hero.
 * \author Chupee
 * \date 18/02/2014
 */
#include "HeroAnimatedSpriteComponent.h"

#include "core/SynthActor.h"
#include "core/ActorType.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"

#include "events/EditMoveEvent.h"
#include "events/ChangePositionEvent.h"
#include "events/JumpEvent.h"
#include "events/InterruptMoveEvent.h"
#include "events/ChangeNodeOWnerEvent.h"
#include "events/ToggleLightEvent.h"
#include "events/DeathEvent.h"
#include "events/WinEvent.h"
#include "events/ResetLevelEvent.h"

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
	core::ActorType eActorType = static_cast<core::SynthActor*>(_owner)->getActorType();
	_pBatchNode = graphicManager->getBatchNode(eActorType);
	_pFrameCache = graphicManager->getFrameCache(eActorType);

	if(_pBatchNode != nullptr && _pFrameCache != nullptr) {
		// position
		_pBatchNode->setPosition(geometryComponent->getPosition());

		// animation
		_pSprite = cocos2d::Sprite::createWithSpriteFrameName("walk_0.png");
		_pBatchNode->addChild(_pSprite);
		_pParent->addChild(_pBatchNode, 1, 3);

		//TODO: add idle animation
		_eState = ActorState::IDLE_STATE;
		_eCurrentAnimType = AnimationType::IDLE;
		//cocos2d::Animation* walkAnimation = graphicManager->getAnimation(_sCurrentAnimName, _pFrameCache);
		//cocos2d::Animate* walkAnimate = cocos2d::Animate::create(walkAnimation);
		//walkAnimate->retain();
		//_pSprite->runAction(cocos2d::RepeatForever::create( walkAnimate ));
	}
}

void HeroAnimatedSpriteComponent::initListeners() {
	AnimatedSpriteComponent::initListeners();
	_pEditMoveEventListener = cocos2d::EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onEditMove, this));
	_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onChangePosition, this));
	_pJumpEventListener = cocos2d::EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onJump, this));
	_pInterruptMoveEventListener = cocos2d::EventListenerCustom::create(events::InterruptMoveEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onInterruptMove, this));
	_pChangeNodeOwnerEventListener = cocos2d::EventListenerCustom::create(events::ChangeNodeOwnerEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onChangeNodeOwner, this));
	_pToggleLightEventListener = cocos2d::EventListenerCustom::create(events::ToggleLightEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onToggleLight, this));
	_pDeathEventListener = cocos2d::EventListenerCustom::create(events::DeathEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onDeath, this));
	_pWinEventListener = cocos2d::EventListenerCustom::create(events::WinEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onWin, this));
	_pResetLevelEventListener = cocos2d::EventListenerCustom::create(events::ResetLevelEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onResetLevel, this));
	
	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent*	pEditMoveEvent	= static_cast<events::EditMoveEvent*>(pEvent);
    core::SynthActor*		pSource			= static_cast<core::SynthActor*>(pEditMoveEvent->getSource());
    core::SynthActor*		pOwner			= static_cast<core::SynthActor*>(_owner);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	_eCurrentAnimType = AnimationType::WALK;
	_eState = ActorState::ON_FLOOR_STATE;
	cocos2d::Animation* walkAnimation = graphicManager->getAnimation(_eCurrentAnimType, _pFrameCache);
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
