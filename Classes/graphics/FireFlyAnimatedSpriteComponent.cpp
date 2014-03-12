/*!
 * \file FireflyAnimatedSpriteComponent.cpp
 * \brief Add animated sprite to a firefly
 * \author Chupee
 * \date 18/02/2014
 */
#include "FireFlyAnimatedSpriteComponent.h"

#include "core/SynthActor.h"
#include "core/ActorType.h"
#include "graphics/GraphicManager.h"
#include "physics/GeometryComponent.h"

#include "events/ChangeNodeOwnerEvent.h"

namespace graphics {

FireFlyAnimatedSpriteComponent::FireFlyAnimatedSpriteComponent(Layer* pParent) :
	AnimatedSpriteComponent(pParent) {
}

FireFlyAnimatedSpriteComponent::~FireFlyAnimatedSpriteComponent() {
}

bool FireFlyAnimatedSpriteComponent::init() {
    SynthComponent::init(FireFlyAnimatedSpriteComponent::COMPONENT_TYPE);
	return true;
}

FireFlyAnimatedSpriteComponent* FireFlyAnimatedSpriteComponent::create(Layer* pParent) {
	FireFlyAnimatedSpriteComponent* pRet = new FireFlyAnimatedSpriteComponent(pParent);
    if (pRet != NULL && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

void FireFlyAnimatedSpriteComponent::onEnter() {
	physics::GeometryComponent* geometryComponent = static_cast<physics::GeometryComponent*>(_owner->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(geometryComponent != NULL, "HeroAnimatedSpriteComponent need a GeometryComponent added to its owner");

	GraphicManager* graphicManager = GraphicManager::getInstance();
	core::ActorType eActorType = static_cast<core::SynthActor*>(_owner)->getActorType();
	SpriteBatchNode* pBatchNode = graphicManager->getBatchNode();
	SpriteFrameCache* pFrameCache = graphicManager->getFrameCache();

	if(pBatchNode != nullptr && pFrameCache != nullptr) {
		SpriteFrame* pFrame = pFrameCache->getSpriteFrameByName("iddle_4.png");
		_pSprite = cocos2d::Sprite::createWithSpriteFrame(pFrame);
		_pSprite->setPosition(geometryComponent->getPosition());
		pBatchNode->addChild(_pSprite);
		if (_pParent->getChildByTag(3) == nullptr) {
			_pParent->addChild(pBatchNode, 1, 3);
		}
		
		// Add idle animation
		switch(eActorType) {

		case(core::ActorType::BLUE_FIREFLY) :
			_eCurrentAnimType = AnimationType::BLUE_FIREFLY;
			break;

		case(core::ActorType::RED_FIREFLY) :
			_eCurrentAnimType = AnimationType::RED_FIREFLY;
			break;

		case(core::ActorType::GREEN_FIREFLY) :
			_eCurrentAnimType = AnimationType::GREEN_FIREFLY;
			break;

		default :
			CCLOG("ACTOR IS NOT A FIREFLY, CANNOT BE ANIMATED WITH A FIREFLY ANIMATED SPRITE");
			break;

		} 
		
		GraphicManager* graphicManager = GraphicManager::getInstance();
		core::SynthAnimation* pAnimation = graphicManager->getAnimation(_eCurrentAnimType);
		Animate* animate = Animate::create(pAnimation->getAnimation());	
		runAnimation(pAnimation, animate);
		
	}
}

void FireFlyAnimatedSpriteComponent::initListeners() {
    AnimatedSpriteComponent::initListeners();
	_pChangeNodeOwnerEventListener = cocos2d::EventListenerCustom::create(events::ChangeNodeOwnerEvent::EVENT_NAME, CC_CALLBACK_1(FireFlyAnimatedSpriteComponent::onChangeNodeOwner, this));
	
	// Add listeners to dispacher
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pChangeNodeOwnerEventListener, 1);
}

void FireFlyAnimatedSpriteComponent::onChangeNodeOwner(EventCustom* pEvent) {
}

}  // namespace graphics
