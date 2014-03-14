/*!
 * \file LightSwitchSoundComponent.cpp
 * \brief The lightswitch can make sounds
 * \author Chupee
 * \date 14/03/2014
 */
#include "LightSwitchSoundComponent.h"
#include "core/SynthActor.h"
#include "events/ToggleLightEvent.h"

namespace sounds {

LightSwitchSoundComponent::LightSwitchSoundComponent() :
	SoundComponent() {
}

LightSwitchSoundComponent::~LightSwitchSoundComponent() {
}

LightSwitchSoundComponent* LightSwitchSoundComponent::create() {
	LightSwitchSoundComponent* pRet = new LightSwitchSoundComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void LightSwitchSoundComponent::initListeners() {
	// Listeners initialization
	_pToggleLightEventListener = cocos2d::EventListenerCustom::create(events::ToggleLightEvent::EVENT_NAME, CC_CALLBACK_1(LightSwitchSoundComponent::onToggleLight, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pToggleLightEventListener, 1);
}

void LightSwitchSoundComponent::onToggleLight(EventCustom* pEvent) {

	events::ToggleLightEvent* pToggleLightEvent	= static_cast<events::ToggleLightEvent*>(pEvent);
    core::SynthActor* pSource							= static_cast<core::SynthActor*>(pToggleLightEvent->getSource());
    core::SynthActor* pTarget							= static_cast<core::SynthActor*>(pToggleLightEvent->getTarget());
    core::SynthActor* pOwner							= static_cast<core::SynthActor*>(_owner);

	_eCurrentTag = SoundType::LIGHTSWITCH;

    if (pTarget->getActorID() == pOwner->getActorID()) {
		CCLOG("RUN LIGHTSWITCH SOUND EFFECT");
		playSound(_eCurrentTag);
    }
    else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }

}

}  // namespace sounds
