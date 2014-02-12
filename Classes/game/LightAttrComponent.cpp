/*!
 * \file LightAttrComponent.h
 * \brief Component giving a colored light to a SynthActor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "LightAttrComponent.h"

namespace game {

char* LightAttrComponent::COMPONENT_TYPE;

LightAttrComponent::LightAttrComponent() {
}

LightAttrComponent::~LightAttrComponent() {
}

bool LightAttrComponent::init() {
	SynthComponent::init(LightAttrComponent::COMPONENT_TYPE);
	return true;
}

LightAttrComponent* LightAttrComponent::create(Color4B * pColor) {
	LightAttrComponent* pRet = new LightAttrComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_pColor =			pColor;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void LightAttrComponent::onChangeIntensity(EventCustom* pEvent) {
}


}  // namespace game
