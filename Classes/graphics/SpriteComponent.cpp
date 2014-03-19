/*!
 * \file SpriteComponent.h
 * \brief Add a sprite image (fixed) to the actor.
 * \author Chupee
 * \date 12/02/2014
 */

#include "SpriteComponent.h"

#include "core/SynthActor.h"
#include "events/ChangePositionEvent.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"


namespace graphics {

const char* SpriteComponent::COMPONENT_TYPE = "SpriteComponent";

SpriteComponent::SpriteComponent() {
}

SpriteComponent::SpriteComponent(Layer* pParent) : 
	SynthComponent(),
	_pParent(pParent),
	_sSpriteName(""),
	_pSprite(nullptr) {
}

SpriteComponent::SpriteComponent(std::string sSpriteName, Layer* pParent) :
	SynthComponent(),
	_sSpriteName(sSpriteName),
	_pParent(pParent) {
	// Create sprite
	graphics::GraphicManager* graphicManager = graphics::GraphicManager::getInstance();
	_pSprite = graphicManager->createSprite(_sSpriteName);
	
	_pParent->addChild(_pSprite, 1000, 2);
}

SpriteComponent::~SpriteComponent() {
	EventDispatcher::getInstance()->removeEventListener(_pChangePositionEventListener);
}

bool SpriteComponent::init() {
    SynthComponent::init(SpriteComponent::COMPONENT_TYPE);
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
	// Listeners initialization
	_pChangePositionEventListener = cocos2d::EventListenerCustom::create(events::ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onChangePosition, this));

	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionEventListener, 1);
}

void SpriteComponent::onChangePosition(EventCustom* pEvent) {
	events::ChangePositionEvent* pChangePosEvent = static_cast<events::ChangePositionEvent*>(pEvent);
	core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
	core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pChangePosEvent->getSource());
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		_pSprite->setPosition(pChangePosEvent->getCurrentPosition());
	}
}

void SpriteComponent::onEnter() {
	physics::GeometryComponent* geometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(geometryComponent != NULL, "SpriteComponent need a GeometryComponent added to its owner");
	if(_pSprite != nullptr) {
		_pSprite->setPosition(geometryComponent->getPosition());
		_pSprite->setAnchorPoint(geometryComponent->getAnchorPoint());
		_pSprite->setRotation(-geometryComponent->getRotationAngle());
	}
}

}  // namespace graphics
