/*!
 * \file HeroSoundComponent.cpp
 * \brief The hero can make sounds !
 * \author Chupee
 * \date 13/03/2014
 */

#include "HeroSoundComponent.h"
#include "core/SynthActor.h"
#include "sounds/SoundManager.h"

#include "events/JumpEvent.h"

namespace sounds {

HeroSoundComponent::HeroSoundComponent() :
	SoundComponent() {
}

HeroSoundComponent::~HeroSoundComponent() {
}

HeroSoundComponent* HeroSoundComponent::create() {
	HeroSoundComponent* pRet = new HeroSoundComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void HeroSoundComponent::initListeners() {

	SoundComponent::initListeners();

	// Listeners initialization
	_pJumpEventListener = cocos2d::EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(HeroSoundComponent::onJump, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
}

void HeroSoundComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroSoundComponent::onJump(EventCustom* pEvent) {

	events::JumpEvent* pJumpEvent						= static_cast<events::JumpEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pJumpEvent->getSource());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	_eCurrentTag = SoundType::HERO_START_JUMP;

    if (_eState == core::ActorState::ON_FLOOR_STATE && pSource->getActorID() == pOwner->getActorID()) {
		CCLOG("RUN JUMP SOUND EFFECT");
		playSound(_eCurrentTag);
    }
    else {
        CCLOG("JUMP EVENT RECEIVED BUT ID NOT THE SAME");
    }

}

void HeroSoundComponent::onInterruptMove(EventCustom* pEvent) {
}

void HeroSoundComponent::onHeroDeath(EventCustom* pEvent) {
}

void HeroSoundComponent::onPeriodicEvent(EventCustom* pEvent) {
}

}  // namespace sounds
