/*!
 * \file SpriteComponent.h
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 12/02/2014
 */
#include "SpriteComponent.h"
#include "events/EditMoveEvent.h"


namespace graphics {

const char* SpriteComponent::COMPONENT_TYPE = "SpriteComponent";

SpriteComponent::SpriteComponent() {

}

SpriteComponent::~SpriteComponent() {
}

bool SpriteComponent::init() {
    SynthComponent::init(SpriteComponent::COMPONENT_TYPE);
	return true;
}

SpriteComponent* SpriteComponent::create(std::string sSpriteName, Layer* pParent) {
	SpriteComponent* pRet = new SpriteComponent();
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
		pRet->_sSpriteName =			sSpriteName;
		pRet->_pParent =				pParent;
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void SpriteComponent::initListeners() {
	_pEditMoveEventListener = cocos2d::EventListenerCustom::create(events::EditMoveEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onEditMove, this));
}

void SpriteComponent::onEditMove(EventCustom* pEvent) {
}

}  // namespace graphics
