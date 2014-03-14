/*!
 * \file FireflySoundComponent.cpp
 * \brief Fireflies can make sounds !
 * \author Chupee
 * \date 13/03/2014
 */
#include "FireflySoundComponent.h"

#include "sounds/SoundManager.h"
#include "physics/GeometryComponent.h"

#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangePositionEvent.h"

namespace sounds {

FireflySoundComponent::FireflySoundComponent() :
	SoundComponent() {
}

FireflySoundComponent::~FireflySoundComponent() {
}

FireflySoundComponent* FireflySoundComponent::create() {
	FireflySoundComponent* pRet = new FireflySoundComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void FireflySoundComponent::initListeners() {
	// Listeners initialization
	_pChangeNodeOwnerEventListener = cocos2d::EventListenerCustom::create(events::ChangeNodeOwnerEvent::EVENT_NAME, CC_CALLBACK_1(FireflySoundComponent::onChangeNodeOwner, this));
	_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangeNodeOwnerEvent::EVENT_NAME, CC_CALLBACK_1(FireflySoundComponent::onChangePosition, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeNodeOwnerEventListener, 1);
	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionEventListener, 1);
}

void FireflySoundComponent::onChangePosition(EventCustom* pEvent) {
	events::ChangePositionEvent* pChangePositionEvent	= static_cast<events::ChangePositionEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pChangePositionEvent->getSource());
	physics::GeometryComponent* pGeometryComponent		= static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	_eCurrentTag = SoundType::FIREFLY_MOVE;
	
    if (pSource->getActorID() == pOwner->getActorID()) {
		if ( ! pChangePositionEvent->getCurrentPosition().equals(pGeometryComponent->getPosition()) ) {
			if(!SoundManager::getInstance()->isPlayingEffect(_eCurrentTag, this)) {
				CCLOG("RUN MOVE FIREFLY SOUND EFFECT");
				playSound(_eCurrentTag);
			}
		} else {
			if(SoundManager::getInstance()->isPlayingEffect(_eCurrentTag, this)) {
				CCLOG("STOP MOVE FIREFLY SOUND EFFECT");
				stopSounds();
			}
		}
    }
    else {
        CCLOG("CHANGE POSITION EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void FireflySoundComponent::onToggleLight(EventCustom* pEvent) {

}

void FireflySoundComponent::onChangeNodeOwner(EventCustom* pEvent) {

	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent	= static_cast<events::ChangeNodeOwnerEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getSource());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	_eCurrentTag = SoundType::FIREFLY_INTERACT;

    if (pSource->getActorID() == pOwner->getActorID()) {
		CCLOG("RUN INTERACT FIREFLY SOUND EFFECT");
		playSound(_eCurrentTag);
    }
    else {
        CCLOG("CHANGE NODE OWNER EVENT RECEIVED BUT ID NOT THE SAME");
    }

}

}  // namespace sounds
