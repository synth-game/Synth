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
#include "graphics/GraphicManager.h"

namespace graphics {

AnimatedSpriteComponent::AnimatedSpriteComponent() {

}

AnimatedSpriteComponent::AnimatedSpriteComponent(Layer* pParent)
	: SpriteComponent(pParent)
	, _eState(core::ActorState::IDLE_STATE)
	, _eCurrentAnimType(AnimationType::HERO_IDLE) {
}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangePositionEventListener);
}

void AnimatedSpriteComponent::initListeners() {
	// Listeners initialization
	_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(AnimatedSpriteComponent::onChangePosition, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionEventListener, 1);
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

void AnimatedSpriteComponent::runAnimation(core::SynthAnimation* pAnimation, Animate* pAnimate) {
	//CCLOG("AnimatedSpriteComponent::runAnimation RUN ANIMATION WITH TAG : %d", pAnimation->getTag());
	_pSprite->stopAllActions();
	if(pAnimation->isLoop()) {
		_pSprite->runAction(cocos2d::RepeatForever::create(pAnimate));
	} else {
		if(
		_pSprite->runAction(Sequence::createWithTwoActions(Repeat::create(pAnimate, 1), CallFunc::create(CC_CALLBACK_0(AnimatedSpriteComponent::requestNextAnimation, this)))));
	}
}

void AnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
	events::ChangePositionEvent* pChangePosEvent = static_cast<events::ChangePositionEvent*>(pEvent);
	core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pChangePosEvent->getSource());
	GraphicManager* graphicManager = GraphicManager::getInstance();
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		_pSprite->setPosition(pChangePosEvent->getCurrentPosition());
	}
}

}  // namespace graphics
