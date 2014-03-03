/*!
 * \file NodeOwnerComponent.cpp
 * \brief Component that makes the actor the owner of an other actor.
 * \author Chupee
 * \date 26/02/2014
 */
#include "NodeOwnerComponent.h"
#include "core/SynthActor.h"
#include "game/LightAttrComponent.h"

#include "events/ToggleLightEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeNodeOwnerEvent.h"

namespace game {
const char* NodeOwnerComponent::COMPONENT_TYPE = "NodeOwnerComponent";

NodeOwnerComponent::NodeOwnerComponent()
	: SynthComponent() {
}

NodeOwnerComponent::~NodeOwnerComponent() {
}

bool NodeOwnerComponent::init() {
	SynthComponent::init(NodeOwnerComponent::COMPONENT_TYPE);
	return true;
}

NodeOwnerComponent* NodeOwnerComponent::create(Node* pOwnedNode) {
	NodeOwnerComponent* pRet = new NodeOwnerComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_pOwnedNode =	pOwnedNode;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void NodeOwnerComponent::initListeners() {
	_pToggleLightEventListener = cocos2d::EventListenerCustom::create(events::ToggleLightEvent::EVENT_NAME, CC_CALLBACK_1(NodeOwnerComponent::onToggleLight, this));
	_pChangeNodeOwnerEventListener = cocos2d::EventListenerCustom::create(events::ChangeNodeOwnerEvent::EVENT_NAME, CC_CALLBACK_1(NodeOwnerComponent::onChangeNodeOwner, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pToggleLightEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeNodeOwnerEventListener, 1);
}

void NodeOwnerComponent::onToggleLight(EventCustom* pEvent) {
	events::ToggleLightEvent* pToggleLightEvent					= static_cast<events::ToggleLightEvent*>(pEvent);
    core::SynthActor* pSource									= static_cast<core::SynthActor*>(pToggleLightEvent->getSource());
    core::SynthActor* pOwner									= static_cast<core::SynthActor*>(_owner);

	if (pSource->getActorID() == pOwner->getActorID() && pOwner->getActorType() == core::ActorType::LIGHTSWITCH) {
		core::SynthActor* pLamp = static_cast<core::SynthActor*>(getOwnedNode());
		core::SynthActor* pFirefly = static_cast<core::SynthActor*>(static_cast<game::NodeOwnerComponent*>(pLamp->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE))->getOwnedNode());

		game::LightAttrComponent* pLightAttrComponent = static_cast<game::LightAttrComponent*>(pFirefly->getComponent(game::LightAttrComponent::COMPONENT_TYPE));
		CCASSERT(pLightAttrComponent != nullptr, "NodeOwnerComponent needs a LightAttrComponent added to its owner");
		if(pToggleLightEvent->isOn()) {
			pLightAttrComponent->setIntensity(1.f);
		} else {
			pLightAttrComponent->setIntensity(0.f);
		}
    } else {
        CCLOG("TOGGLE LIGHT EVENT RECEIVED BUT ID NOT THE SAME");
    }
}

void NodeOwnerComponent::onChangeNodeOwner(EventCustom* pEvent) {
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent			= static_cast<events::ChangeNodeOwnerEvent*>(pEvent);
	core::SynthActor* pSource									= static_cast<core::SynthActor*>(pChangeNodeOwnerEvent->getOwned());
	core::SynthActor* pOwnedNode								= static_cast<core::SynthActor*>(_pOwnedNode);

    if (pSource->getActorID() == pOwnedNode->getActorID()) {
		_pOwnedNode = pSource;
    } else {
        CCLOG("CHANGE NODE OWNER EVENT : THIS ACTOR IS NOT THE OWNER");
    }
}

}  // namespace game
