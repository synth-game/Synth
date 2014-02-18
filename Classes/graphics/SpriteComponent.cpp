/*!
 * \file SpriteComponent.h
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 12/02/2014
 */

#include "SpriteComponent.h"
#include "events/EditMoveEvent.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"


namespace graphics {

const char* SpriteComponent::COMPONENT_TYPE = "SpriteComponent";

SpriteComponent::SpriteComponent() {

}
SpriteComponent::SpriteComponent(std::string sSpriteName, Layer* pParent) :
	SynthComponent(),
	_sSpriteName(sSpriteName),
	_pParent(pParent) {
	// Create sprite
	graphics::GraphicManager* graphicManager = graphics::GraphicManager::getInstance();
	_pSprite = graphicManager->createSprite(_sSpriteName);
	_pParent->addChild(_pSprite, 0, 2);
}

SpriteComponent::~SpriteComponent() {
}

bool SpriteComponent::init() {
    SynthComponent::init(SpriteComponent::COMPONENT_TYPE);
	initListeners();
	return true;
}

SpriteComponent* SpriteComponent::create(std::string sSpriteName, Layer* pParent) {
	SpriteComponent* pRet = new SpriteComponent(sSpriteName, pParent);
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
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

void SpriteComponent::onEnter() {
	physics::GeometryComponent* geometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(geometryComponent != NULL, "SpriteComponent need a GeometryComponent added to its owner");
	if(_pSprite != nullptr) {
		_pSprite->setPosition(geometryComponent->getPosition());
	}
}

}  // namespace graphics
