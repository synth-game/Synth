/*!
 * \file AnimatedSpriteComponent.cpp
 * \brief Abstract class for aminated sprites.
 * \author Chupee
 * \date 18/02/2014
 */
#include "AnimatedSpriteComponent.h"
#include "core/SynthActor.h"
#include "physics/GeometryComponent.h"
#include "events/ChangePositionEvent.h"
#include "events/InterruptMoveEvent.h"
#include "events/ChangeStateEvent.h"
#include "graphics/GraphicManager.h"

namespace graphics {

AnimatedSpriteComponent::AnimatedSpriteComponent() {

}

AnimatedSpriteComponent::AnimatedSpriteComponent(Layer* pParent)
	: SpriteComponent(pParent)
	, _eState(core::ActorState::IDLE_STATE)
    , _ePreviousState(core::ActorState::IDLE_STATE)
	, _eCurrentAnimType(AnimationType::NO_ANIMATION){
}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangePositionEventListener);
}

void AnimatedSpriteComponent::initListeners() {
    SpriteComponent::initListeners();
	// Listeners initialization
}
    
bool AnimatedSpriteComponent::actorIsLateralMoving() {
    physics::MovementComponent* pMovementComponent = static_cast<physics::MovementComponent*>(_owner->getComponent(physics::MovementComponent::COMPONENT_TYPE));
    return pMovementComponent->isLateralMoving();
}

void AnimatedSpriteComponent::requestNextAnimation() {
	GraphicManager* graphicManager = GraphicManager::getInstance();
	core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
	AnimationType eNextAnimationType = pAnimation->getNextTag();
	if(eNextAnimationType != graphics::AnimationType::NO_ANIMATION) {
		_eCurrentAnimType = eNextAnimationType;
		core::SynthAnimation* pNextAnimation = graphicManager->getAnimation(_eCurrentAnimType);
		Animate* animate = Animate::create(pNextAnimation->getAnimation());	
		if(pNextAnimation->isLoop()) {
			_pSprite->runAction(RepeatForever::create(animate));
		} else {
			if (pNextAnimation->getNextTag() != graphics::AnimationType::NO_ANIMATION) {
				_pSprite->runAction(Sequence::createWithTwoActions(Repeat::create(animate, 1), CallFunc::create(CC_CALLBACK_0(AnimatedSpriteComponent::requestNextAnimation, this))));
			} else {
				_pSprite->runAction(RepeatForever::create(animate));
			}
		}	
	}
}

void AnimatedSpriteComponent::runAnimation(AnimationType animationType) {
    _eCurrentAnimType = animationType;
    GraphicManager* graphicManager = GraphicManager::getInstance();
    core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
    cocos2d::Animate* animate = cocos2d::Animate::create(pAnimation->getAnimation());
    _pSprite->stopAllActions();
	if(pAnimation->isLoop()) {
		_pSprite->runAction(cocos2d::RepeatForever::create(animate));
	} else {
		if(
		_pSprite->runAction(Sequence::createWithTwoActions(Repeat::create(animate, 1), CallFunc::create(CC_CALLBACK_0(AnimatedSpriteComponent::requestNextAnimation, this)))));
	}
}
    
    String AnimatedSpriteComponent::debugAnimationType(AnimationType type) {
        switch (type) {
            case NO_ANIMATION:
                return "NO_ANIMATION";
                break;
            case HERO_IDLE:
                return "HERO_IDLE";
                break;
            case HERO_START_IDLE:
                return "HERO_START_IDLE";
                break;
            case HERO_WALK:
                return "HERO_WALK";
                break;
            case HERO_STOP_WALK:
                return "HERO_STOP_WALK";
                break;
            case HERO_START_JUMP:
                return "HERO_START_JUMP";
                break;
            case HERO_DURING_JUMP:
                return "HERO_DURING_JUMP";
                break;
            case HERO_JUMP:
                return "HERO_JUMP";
                break;
            case HERO_FALL:
                return "HERO_FALL";
                break;
            case HERO_START_BOUNCE:
                return "HERO_START_BOUNCE";
                break;
            case HERO_BOUNCE:
                return "HERO_BOUNCE";
                break;
            case HERO_STOP_BOUNCE:
                return "HERO_STOP_BOUNCE";
                break;
            case HERO_START_CRAWL:
                return "HERO_START_CRAWL";
                break;
            case HERO_CRAWL:
                return "HERO_CRAWL";
                break;
            case HERO_STOP_CRAWL:
                return "HERO_STOP_CRAWL";
                break;
            case HERO_IDLE_CRAWL:
                return "HERO_IDLE_CRAWL";
                break;
            case HERO_FLY:
                return "HERO_FLY";
                break;
            case HERO_HIT:
                return "HERO_HIT";
                break;
            case HERO_INTERACT:
                return "HERO_INTERACT";
                break;
            case HERO_COUGH:
                return "HERO_COUGH";
                break;
            case HERO_PULL_SWITCH:
                return "HERO_PULL_SWITCH";
                break;
            case HERO_DIE:
                return "HERO_DIE";
                break;
            case HERO_SPAWN:
                return "HERO_SPAWN";
                break;
            case HERO_WIN:
                return "HERO_WIN";
                break;
            case BLUE_FIREFLY:
                return "BLUE_FIREFLY";
                break;
            case RED_FIREFLY:
                return "RED_FIREFLY";
                break;
            case GREEN_FIREFLY:
                return "GREEN_FIREFLY";
                break;
            default:
                return "UNKNOWN ANIMATION";
                break;
        }
    }
    
}  // namespace graphics
