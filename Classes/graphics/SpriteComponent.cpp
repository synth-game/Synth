/* *****************************************************
 *		SpriteComponent.cpp - @ Damaris Ankou - 30/01/14
 ***************************************************** */

#include "SpriteComponent.h"
#include "events/ChangePositionEvent.h"
#include "core/SynthActor.h"

const char* SpriteComponent::COMPONENT_TYPE = "SpriteComponent";

SpriteComponent::SpriteComponent()
	: SynthComponent()
	, _sFilePath()
	, _pSprite(nullptr)
	, _pParentLayer(nullptr) {

}

SpriteComponent::~SpriteComponent() {

}

bool SpriteComponent::init() {
	SynthComponent::init(SpriteComponent::COMPONENT_TYPE);
	_pSprite = Sprite::create(_sFilePath.c_str());
	_pParentLayer->addChild(_pSprite);
	return true;
}

SpriteComponent* SpriteComponent::create(std::string sFilePath, Layer* pParentLayer) {
	SpriteComponent* pRet = new SpriteComponent();
	if (pRet != nullptr) {
		pRet->autorelease();
		pRet->_sFilePath = sFilePath;
		pRet->_pParentLayer = pParentLayer;
		pRet->init();
	} else { 
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void SpriteComponent::initListeners() {
	_pChangePositionListener = EventListenerCustom::create(ChangePositionEvent::EVENT_NAME, CC_CALLBACK_1(SpriteComponent::onChangePosition, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangePositionListener, 1);
}

void SpriteComponent::onChangePosition(EventCustom* pEvent) {
	ChangePositionEvent* pChangePosEvent = static_cast<ChangePositionEvent*>(pEvent);
	SynthActor* pOwner = static_cast<SynthActor*>(_owner);
	SynthActor* pEventSource = static_cast<SynthActor*>(pChangePosEvent->getSource());
	if (pOwner->getActorID() == pEventSource->getActorID()) {
		_pSprite->setPosition(pChangePosEvent->getCurrentPosition());
	}
}