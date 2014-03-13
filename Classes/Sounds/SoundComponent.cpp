/*!
 * \file SoundComponent.cpp
 * \brief The actor who have this component can make sounds or music
 * \author Chupee
 * \date 27/02/2014
 */
#include "SoundComponent.h"
#include "SoundManager.h"
#include "core/ActorState.h"

namespace sounds {

const char* SoundComponent::COMPONENT_TYPE = "SoundComponent";

SoundComponent::SoundComponent()
	: SynthComponent(),
	_eCurrentTag(SoundType::NO_SOUND),
	_eState(core::ActorState::NO_STATE) {

}

SoundComponent::~SoundComponent() {
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

}

void SoundComponent::playSound(SoundType type) {
	SoundManager::getInstance()->playEffect(this, type);
}


}  // namespace sounds
