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

namespace graphics {

AnimatedSpriteComponent::AnimatedSpriteComponent() {

}

AnimatedSpriteComponent::AnimatedSpriteComponent(Layer* pParent)
	: SpriteComponent(pParent)
	, _pFrameCache(nullptr)
	, _pBatchNode(nullptr)
	, _eState(ActorState::IDLE_STATE)
	, _eCurrentAnimType(AnimationType::IDLE) {
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
}

void AnimatedSpriteComponent::onChangePosition(EventCustom* pEvent) {
	events::ChangePositionEvent* pChangePosEvent = static_cast<events::ChangePositionEvent*>(pEvent);
	core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pChangePosEvent->getSource());
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		_pBatchNode->setPosition(pChangePosEvent->getCurrentPosition());
	}
}

}  // namespace graphics
