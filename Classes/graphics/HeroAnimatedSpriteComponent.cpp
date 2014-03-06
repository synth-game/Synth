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
#include "events/ChangeStateEvent.h"

namespace graphics {

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
	SpriteBatchNode* pBatchNode = graphicManager->getBatchNode();
	SpriteFrameCache* pFrameCache = graphicManager->getFrameCache();

	if(pBatchNode != nullptr && pFrameCache != nullptr) {
		SpriteFrame* pFrame = pFrameCache->getSpriteFrameByName("iddle_4.png");
		_pSprite = cocos2d::Sprite::createWithSpriteFrame(pFrame);
		_pSprite->setPosition(geometryComponent->getPosition());
		pBatchNode->addChild(_pSprite);
		_pParent->addChild(pBatchNode, 1, 3);
		
		// Add idle animation
		_eCurrentAnimType = AnimationType::HERO_IDLE;
		GraphicManager* graphicManager = GraphicManager::getInstance();
		core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
		Animate* animate = Animate::create(pAnimation->getAnimation());	
		runAnimation(pAnimation, animate);
		
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
	_pChangeStateEventListener = cocos2d::EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(HeroAnimatedSpriteComponent::onChangeState, this));
	
	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEditMoveEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
}

void HeroAnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {

}

void HeroAnimatedSpriteComponent::onEditMove(EventCustom* pEvent) {
	events::EditMoveEvent*	pEditMoveEvent	= static_cast<events::EditMoveEvent*>(pEvent);
    core::SynthActor*		pSource			= static_cast<core::SynthActor*>(pEditMoveEvent->getSource());
    core::SynthActor*		pOwner			= static_cast<core::SynthActor*>(_owner);

    if (pSource->getActorID() == pOwner->getActorID()) {
		
		if (pEditMoveEvent->isStartMoving()) {
			// the movement starts
			switch (_eState) {
			case core::ActorState::ON_FLOOR_STATE :
				_eCurrentAnimType = AnimationType::HERO_WALK;
				break;
			case core::ActorState::STUCK_STATE :
				_eCurrentAnimType = AnimationType::HERO_CRAWL;
				break;
			case core::ActorState::ON_AIR_STATE :
				_eCurrentAnimType = AnimationType::HERO_FLY;
				break;
			case core::ActorState::BOUNCE_STATE :
				_eCurrentAnimType = AnimationType::HERO_BOUNCE;
				break;
			default:
				_eCurrentAnimType = AnimationType::HERO_WALK;
				break;
			}
			GraphicManager* graphicManager = GraphicManager::getInstance();
			core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
			Animate* animate = Animate::create(pAnimation->getAnimation());	
			if (pEditMoveEvent->getDirection().x < 0) {
				_pSprite->setFlippedX(true);
			}
			else if(pEditMoveEvent->getDirection().x > 0) {
				_pSprite->setFlippedX(false);
			}
			runAnimation(pAnimation, animate);
		} else {
			// the movement stops
			switch (_eState) {
			case core::ActorState::ON_FLOOR_STATE :
				_eCurrentAnimType = AnimationType::HERO_STOP_WALK;
				break;
			case core::ActorState::STUCK_STATE :
				_eCurrentAnimType = AnimationType::HERO_STOP_CRAWL;
				break;
			case core::ActorState::ON_AIR_STATE :
				_eCurrentAnimType = AnimationType::HERO_FLY;
				break;
			case core::ActorState::BOUNCE_STATE :
				_eCurrentAnimType = AnimationType::HERO_BOUNCE;
				break;
			default:
				_eCurrentAnimType = AnimationType::HERO_STOP_WALK;
				break;
			}
			GraphicManager* graphicManager = GraphicManager::getInstance();
			core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
			Animate* animate = Animate::create(pAnimation->getAnimation());	
			// inverted in this case
			if (pEditMoveEvent->getDirection().x < 0) {
				_pSprite->setFlippedX(false);
			}
			else if(pEditMoveEvent->getDirection().x > 0) {
				_pSprite->setFlippedX(true);
			}
			runAnimation(pAnimation, animate);
		}
    }
    else {
        CCLOG("MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void HeroAnimatedSpriteComponent::onJump(EventCustom* pEvent) {

	events::JumpEvent* pJumpEvent						= static_cast<events::JumpEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pJumpEvent->getSource());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	_eCurrentAnimType = AnimationType::HERO_START_JUMP;
	core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
	cocos2d::Animate* animate = cocos2d::Animate::create(pAnimation->getAnimation());

    if (pSource->getActorID() == pOwner->getActorID()) {
		runAnimation(pAnimation, animate);
    }
    else {
        CCLOG("JUMP EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void HeroAnimatedSpriteComponent::onInterruptMove(EventCustom* pEvent) {

	events::InterruptMoveEvent* pInterruptMoveEvent		= static_cast<events::InterruptMoveEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pInterruptMoveEvent->getSource());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	_eCurrentAnimType = AnimationType::HERO_IDLE;
	_eState = core::ActorState::IDLE_STATE;

    if (pSource->getActorID() == pOwner->getActorID()) {
		_pSprite->stopAllActions();
    }
    else {
        CCLOG("INTERRUPT MOVE EVENT RECEIVED BUT ID NOT THE SAME");
    }

}

void HeroAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent) {

	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = static_cast<events::ChangeNodeOwnerEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getSource());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	_eCurrentAnimType = AnimationType::HERO_INTERACT;
	_eState = core::ActorState::ON_FLOOR_STATE;
	core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
	cocos2d::Animate* animate = cocos2d::Animate::create(pAnimation->getAnimation());

    if (pSource->getActorID() == pOwner->getActorID()) {
		_pSprite->stopAllActions();
		_pSprite->runAction(animate); // not looping
    }
    else {
        CCLOG("CHANGE NODE OWNER EVENT RECEIVED BUT ID NOT THE SAME");
    }

}

void HeroAnimatedSpriteComponent::onToggleLight(EventCustom* pEvent) {

	events::ToggleLightEvent*	pToggleLightEvent	= static_cast<events::ToggleLightEvent*>(pEvent);
    core::SynthActor*		pSource			= static_cast<core::SynthActor*>(pToggleLightEvent->getSource());
    core::SynthActor*		pOwner			= static_cast<core::SynthActor*>(_owner);

	GraphicManager* graphicManager = GraphicManager::getInstance();
	_eCurrentAnimType = AnimationType::HERO_PULL_SWITCH;
	_eState = core::ActorState::ON_FLOOR_STATE;
	core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
	cocos2d::Animate* animate = cocos2d::Animate::create(pAnimation->getAnimation());

    if (pSource->getActorID() == pOwner->getActorID()) {
		_pSprite->stopAllActions();
		_pSprite->runAction(cocos2d::RepeatForever::create(animate));
    }
    else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void HeroAnimatedSpriteComponent::onDeath(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onWin(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onResetLevel(EventCustom* pEvent) {
}

void HeroAnimatedSpriteComponent::onChangeState(EventCustom* pEvent) {

	events::ChangeStateEvent*	pChangeStateEvent	= static_cast<events::ChangeStateEvent*>(pEvent);
    core::SynthActor*			pSource				= static_cast<core::SynthActor*>(pChangeStateEvent->getSource());
    core::SynthActor*			pOwner				= static_cast<core::SynthActor*>(_owner);

	 if (pSource->getActorID() == pOwner->getActorID()) {
		 _eState = pChangeStateEvent->getNewState();
    }
    else {
        CCLOG("CHANGE STATE EVENT RECEIVED BUT ID NOT THE SAME");
    }

}



}  // namespace graphics
