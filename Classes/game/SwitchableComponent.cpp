/*!
 * \file SwitchableComponent.cpp
 * \brief The actor can be turned on and off
 * \author Chupee
 * \date 14/03/2014
 */
#include "SwitchableComponent.h"
#include "core/SynthActor.h"
#include "game/GameManager.h"
#include "game/LightAttrComponent.h"
#include "game/NodeOwnerComponent.h"

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
	_pToggleLightEventListener = cocos2d::EventListenerCustom::create(events::ToggleLightEvent::EVENT_NAME, CC_CALLBACK_1(SwitchableComponent::onToggleLight, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pToggleLightEventListener, 1);
}

void SwitchableComponent::onToggleLight(EventCustom* pEvent) {
	events::ToggleLightEvent* pToggleLightEvent					= static_cast<events::ToggleLightEvent*>(pEvent);
    game::GameManager* pGameManager								= static_cast<game::GameManager*>(pToggleLightEvent->getSource());
    core::SynthActor* pOwner									= static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pTarget									= static_cast<core::SynthActor*>(pToggleLightEvent->getTarget());
	game::NodeOwnerComponent * pTargetNodeOwnerComponent		= static_cast<game::NodeOwnerComponent*>(pTarget->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	CCASSERT(pTargetNodeOwnerComponent != nullptr && static_cast<core::SynthActor*>(pTargetNodeOwnerComponent->getOwnedNode())->getActorType() == core::ActorType::LIGHT, "The target of the toggle light event has to own a light");
	core::SynthActor* pLamp = static_cast<core::SynthActor*>(pTargetNodeOwnerComponent->getOwnedNode());

	if (pLamp->getActorID() == pOwner->getActorID()) {
		CCLOG("TOGGLE LIGHT EVENT RECEIVED");
		game::NodeOwnerComponent * pLampNodeOwnerComponent		= static_cast<game::NodeOwnerComponent*>(pLamp->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
		CCASSERT(pLampNodeOwnerComponent != nullptr , "The lamp owned by the target of toggle light event has to have a node owner component");
		_bOn = pToggleLightEvent->isOn();
		pGameManager->getLevelSprite()->updateLight(pLamp);

    } else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }
}


}  // namespace game
