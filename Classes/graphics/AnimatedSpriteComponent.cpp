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
	, _eState(ActorState::IDLE_STATE)
	, _eCurrentAnimType(AnimationType::HERO_IDLE) {
}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {
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
	if(eNextAnimationType != NULL) {
		_eCurrentAnimType = eNextAnimationType;
		core::SynthAnimation* pNextAnimation = graphicManager->getAnimation(_eCurrentAnimType);
		Animate* animate = Animate::create(pNextAnimation->getAnimation());	
		if(pNextAnimation->isLoop()) {
			_pSprite->runAction(RepeatForever::create(animate));
		} else {
			if (pNextAnimation->getNextTag() != NULL) {
				_pSprite->runAction(Sequence::createWithTwoActions(Repeat::create(animate, 0), CallFunc::create(CC_CALLBACK_0(AnimatedSpriteComponent::requestNextAnimation, this))));
			} else {
				_pSprite->runAction(RepeatForever::create(animate));
			}
		}	
	}
}

void AnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
	events::ChangePositionEvent* pChangePosEvent = static_cast<events::ChangePositionEvent*>(pEvent);
	core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pChangePosEvent->getSource());
	GraphicManager* graphicManager = GraphicManager::getInstance();
	SpriteBatchNode* pBatchNode = graphicManager->getBatchNode();
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		pBatchNode->setPosition(pChangePosEvent->getCurrentPosition());
	}
}

}  // namespace graphics
