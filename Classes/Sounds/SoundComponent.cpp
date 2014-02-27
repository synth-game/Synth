/*!
 * \file SoundComponent.cpp
 * \brief The actor who have this component can make sounds or music
 * \author Chupee
 * \date 27/02/2014
 */
#include "SoundComponent.h"

namespace sounds {

const char* SoundComponent::COMPONENT_TYPE = "SoundComponent";

SoundComponent::SoundComponent() {
}

SoundComponent::~SoundComponent() {
}


bool SoundComponent::init() {
	return false;
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

}

void SoundComponent::onSetStateEvent(EventCustom* pEvent) {
}


}  // namespace sounds
