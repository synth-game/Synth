/*!
 * \file SwitchableComponent.cpp
 * \brief The actor can be turned on and off
 * \author Chupee
 * \date 14/03/2014
 */
#include "SwitchableComponent.h"
#include "core/SynthActor.h"
#include "game/LightAttrComponent.h"

#include "events/ToggleLightEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeNodeOwnerEvent.h"

namespace game {
const char* SwitchableComponent::COMPONENT_TYPE = "SwitchableComponent";

SwitchableComponent::SwitchableComponent()
	: SynthComponent(),
	_bOn(true) {
}

SwitchableComponent::~SwitchableComponent() {
}

bool SwitchableComponent::init() {
	SynthComponent::init(SwitchableComponent::COMPONENT_TYPE);
	return true;
}

SwitchableComponent* SwitchableComponent::create(bool bOn) {
	SwitchableComponent* pRet = new SwitchableComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_bOn = bOn;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void SwitchableComponent::initListeners() {
	_pToggleLightEventListener = cocos2d::EventListenerCustom::create(events::ToggleLightEvent::EVENT_NAME, CC_CALLBACK_1(NodeOwnerComponent::onToggleLight, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pToggleLightEventListener, 1);
}

void SwitchableComponent::onToggleLight(EventCustom* pEvent) {
	events::ToggleLightEvent* pToggleLightEvent					= static_cast<events::ToggleLightEvent*>(pEvent);
    core::SynthActor* pSource									= static_cast<core::SynthActor*>(pToggleLightEvent->getSource());
    core::SynthActor* pOwner									= static_cast<core::SynthActor*>(_owner);

	if (pSource->getActorID() == pOwner->getActorID() && pOwner->getActorType() == core::ActorType::LIGHTSWITCH) {
		
    } else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }
}


}  // namespace game
