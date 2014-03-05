/*!
 * \file GameManager.cpp
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */

#include "GameManager.h"
#include "core/ActorType.h"
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "physics/FollowMovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "game/NodeOwnerComponent.h"

#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeTargetEvent.h"

#include <SimpleAudioEngine.h>

namespace game {

GameManager::GameManager() 
	: Layer() 
	, _iCurrentLevelId(-1)
	, _fTimeSinceLevelStart(0.f) 
	, _levelActors() 
	, _triggers()
	, _pLevelSprite(nullptr) 
	, _pBackgroundLayer(nullptr) 
	, _pIntermediarLayer(nullptr)
	, _pLevelLayer(nullptr) 
	, _pSkinningLayer(nullptr) 
	, _pSubtitlesLayer(nullptr) 
	, _pParallaxManager(nullptr)
	, _keyPressedCode() {

}

GameManager::~GameManager() {
	_levelActors.clear();
	_triggers.clear();
}

GameManager* GameManager::create() {
	GameManager* pRet = new GameManager();
	if (pRet != nullptr && pRet->init()) {
		CCLOG("GameManager created");
		pRet->autorelease();
	} else {
		CCLOG("GameManager created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameManager::init() {
    bool bTest = true;

	//init Layer
	bTest = Layer::init();

	// activate key event handling
	setKeyboardEnabled(true);

	// activate update function
	scheduleUpdate();

	//init layers
	_pBackgroundLayer = Layer::create();
	_pIntermediarLayer = Layer::create();
	_pLevelLayer = Layer::create();
	_pSkinningLayer = Layer::create();
	_pSubtitlesLayer = Layer::create();
	
	_pParallaxManager = ParallaxNode::create();
	_pParallaxManager->addChild(_pBackgroundLayer, 1, Point(0.7f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pIntermediarLayer, 2, Point(0.8f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pLevelLayer, 3, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSkinningLayer, 4, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSubtitlesLayer, 5, Point(1.f, 1.f), Point(0.f, 0.f));
	Layer::addChild(_pParallaxManager);

	//TEST ZONE - BEGIN
	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	pBgSprite->setAnchorPoint(Point::ZERO);
	_pBackgroundLayer->addChild(pBgSprite);

	hero = new core::SynthActor(core::ActorType::HERO);
	hero->addComponent(physics::GeometryComponent::create(Point(50.f, 50.f), Size(20.f, 90.f), 0.f, Point(0.f, 0.f)));
	hero->addComponent(physics::MovementComponent::create(Point(20.f, 20.f), Point(0.f, -5.f)));
	physics::CollisionComponent* pHeroColComp = physics::CollisionComponent::create();
	Image* pBitmask = new Image();
	pBitmask->initWithImageFile("levels/test/bitmask.png");
	physics::PhysicCollision* pPhyCol = new physics::PhysicCollision(pBitmask, Point(0, pBitmask->getHeight()));
	pHeroColComp->addPhysicCollision(pPhyCol);
	hero->addComponent(pHeroColComp); 

	hero->addComponent(graphics::HeroAnimatedSpriteComponent::create(_pLevelLayer));
	
	LevelSprite* pLevelSprite = LevelSprite::create("levels/test/bitmask.png", hero);
	//pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_0.png")->getTexture(), Point(390.f, 260.f), Color4B::RED);
	//pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_1.png")->getTexture(), Point(100.f, 580.f), Color4B::BLUE);
	//pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_2.png")->getTexture(), Point(590.f, 260.f), Color4B::GREEN);
	_pLevelLayer->addChild(pLevelSprite, 0);

	firefly = new core::SynthActor(core::ActorType::FIREFLY);
	firefly->addComponent(physics::GeometryComponent::create(Point(500.f, 400.f), Size(30.f, 30.f), 0.f, Point(0.f, 0.f)));
	firefly->addComponent(graphics::SpriteComponent::create("sprites/firefly.png", _pLevelLayer));

	hero->addComponent(game::NodeOwnerComponent::create(nullptr));
	firefly->addComponent(physics::FollowMovementComponent::create( Point(7.f, 7.f), firefly ));

	//TEST ZONE - END


	return bTest;
}

void GameManager::update(float fDt) {
	hero->update(fDt);
	firefly->update(fDt);
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(hero->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCLOG("position %2.f, %2.f", pGeometryComponent->getPosition().x, pGeometryComponent->getPosition().y);
}

void GameManager::loadLevel(int iLevelId) {

}

void GameManager::resetLevel() {
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = nullptr;
	events::ChangeTargetEvent* pChangeTargetEvent = nullptr;
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(hero->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	physics::FollowMovementComponent* pFollowMovementComponent = static_cast<physics::FollowMovementComponent*>(firefly->getComponent(physics::FollowMovementComponent::COMPONENT_TYPE));

    auto dispatcher = EventDispatcher::getInstance();

	_keyPressedCode.push(keyCode);

    switch(_keyPressedCode.top()) {
        case EventKeyboard::KeyCode::KEY_Q:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(-1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent LEFT");
            dispatcher->dispatchEvent(pEditMoveEvent);
            break;
            
        case EventKeyboard::KeyCode::KEY_D:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent RIGHT");
            dispatcher->dispatchEvent(pEditMoveEvent);
            break;
            
        case EventKeyboard::KeyCode::KEY_SPACE:
            pJumpEvent = new events::JumpEvent(hero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_Z:
            pJumpEvent = new events::JumpEvent(hero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_P:
		   if (pNodeOwnerComponent->getOwnedNode() == firefly) {
			   pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(firefly, nullptr);
			   CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE WITHOUT OWNED");
			   dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
			   pChangeTargetEvent = new events::ChangeTargetEvent(firefly, firefly);
			   CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
			   dispatcher->dispatchEvent(pChangeTargetEvent);
		   } else {
			   pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(firefly, hero);
			   CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
			   dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
			   pChangeTargetEvent = new events::ChangeTargetEvent(firefly, hero);
			   CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
			   dispatcher->dispatchEvent(pChangeTargetEvent);
		   }
           
           break;
            
        default:
            break;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();

	if(keyCode == _keyPressedCode.top()) {
		switch(keyCode) {
			case EventKeyboard::KeyCode::KEY_Q:
				pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				break;
			case EventKeyboard::KeyCode::KEY_D:
				pEditMoveEvent = new events::EditMoveEvent(hero, Point(-1., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				break;
			case EventKeyboard::KeyCode::KEY_SPACE:
				/*jumpEvent = new ActorJumpEvent(_hero);
				jumpEvent->_bStart = false;
				dispatcher->dispatchEvent(jumpEvent);*/

				break;
			default:
				break;
		}
		_keyPressedCode.pop();
	}
}

Color4B GameManager::getLightColor(core::SynthActor* pLight) {
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorsByTag(std::string sTag) {
	std::vector<core::SynthActor*> emptyVec;
	return emptyVec;
}

//void GameManager::onEditMove(EventCustom* pEvent) { 
//	CCLOG("on edit move gm");
//}

}  // namespace game
