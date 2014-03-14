/*!
 * \file LightAttrComponent.h
 * \brief Component giving a colored light to a SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "LightAttrComponent.h"
#include "Events/ChangeIntensityEvent.h"

namespace game {

const char* LightAttrComponent::COMPONENT_TYPE  = "LightAttrComponent";

LightAttrComponent::LightAttrComponent() 
	: SynthComponent() {
}

LightAttrComponent::~LightAttrComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangeIntensityListener);
}

bool LightAttrComponent::init() {
	SynthComponent::init(LightAttrComponent::COMPONENT_TYPE);
	return true;
}

LightAttrComponent* LightAttrComponent::create(Color4B color) {
	LightAttrComponent* pRet = new LightAttrComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_color =	color;
		pRet->_intensity = color.a;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void LightAttrComponent::initListeners() {
	_pChangeIntensityListener = cocos2d::EventListenerCustom::create(events::ChangeIntensityEvent::EVENT_NAME, CC_CALLBACK_1(LightAttrComponent::onChangeIntensity, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeIntensityListener, 1);
}

void LightAttrComponent::onChangeIntensity(EventCustom* pEvent) {
}


}  // namespace game
