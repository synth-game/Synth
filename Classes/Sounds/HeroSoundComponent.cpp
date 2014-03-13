/*!
 * \file HeroSoundComponent.cpp
 * \brief The hero can make sounds !
 * \author Chupee
 * \date 13/03/2014
 */

#include "HeroSoundComponent.h"

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
	// Listeners initialization
	_pJumpEventListener = cocos2d::EventListenerCustom::create(events::JumpEvent::EVENT_NAME, CC_CALLBACK_1(HeroSoundComponent::onJump, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pJumpEventListener, 1);
}

void HeroSoundComponent::onChangePosition(EventCustom* pEvent) {
}

void HeroSoundComponent::onJump(EventCustom* pEvent) {
}

void HeroSoundComponent::onInterruptMove(EventCustom* pEvent) {
}

void HeroSoundComponent::onHeroDeath(EventCustom* pEvent) {
}

void HeroSoundComponent::onPeriodicEvent(EventCustom* pEvent) {
}

}  // namespace sounds
