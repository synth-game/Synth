/*!
 * \file SoundComponent.cpp
 * \brief The actor who have this component can make sounds or music
 * \author Chupee
 * \date 27/02/2014
 */
#include "SoundComponent.h"
#include "SoundManager.h"
#include "core/ActorState.h"

#include "events/ChangeStateEvent.h"

namespace sounds {

const char* SoundComponent::COMPONENT_TYPE = "SoundComponent";

SoundComponent::SoundComponent()
	: SynthComponent(),
	_eCurrentTag(SoundType::NO_SOUND),
	_eState(core::ActorState::NO_STATE) {

}

SoundComponent::~SoundComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangeStateEventListener);
}


bool SoundComponent::init() {
	SynthComponent::init(SoundComponent::COMPONENT_TYPE);
	return true;
}

SoundComponent* SoundComponent::create() {
	SoundComponent* pRet = new SoundComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void SoundComponent::initListeners() {
	// Listeners initialization
	_pChangeStateEventListener = cocos2d::EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(SoundComponent::onChangeState, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeStateEventListener, 1);
}

void SoundComponent::playSound(SoundType type) {
	stopSounds();
	SoundManager::getInstance()->playEffect(this, type);
}

void SoundComponent::stopSounds() {
	SoundManager::getInstance()->stopEffect(this);
}

void SoundComponent::onChangeState(EventCustom* pEvent) {

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


}  // namespace sounds
