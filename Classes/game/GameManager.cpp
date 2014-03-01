/*!
 * \file GameManager.cpp
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */
#include "GameManager.h"
#include "game/LevelFactory.h"
#include "core/ActorType.h"
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"

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
	, _pParallaxManager(nullptr) {

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
	_pParallaxManager->addChild(_pBackgroundLayer, 1, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pIntermediarLayer, 2, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pLevelLayer, 3, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSkinningLayer, 4, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSubtitlesLayer, 5, Point(1.f, 1.f), Point(0.f, 0.f));
	Layer::addChild(_pParallaxManager);

	//TEST ZONE - BEGIN
	LevelSprite* pLevelSprite = LevelSprite::create("levels/test/bitmask.png");
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_0.png")->getTexture(), Color4F::RED, true);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_1.png")->getTexture(), Color4F::GREEN, true);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_2.png")->getTexture(), Color4F::BLUE, true);
	_pLevelLayer->addChild(pLevelSprite);

	_levelActors = game::LevelFactory::getInstance()->buildActors(_pLevelLayer);

	hero = *find_if(_levelActors.begin(), _levelActors.end(), [](core::SynthActor* actor) { 
						return actor->getActorType() == core::ActorType::HERO;
					});

	//TEST ZONE - END

	return bTest;
}

void GameManager::update(float fDt) {
	for (auto actor : _levelActors) {
		actor->update(fDt);
	}
}

void GameManager::loadLevel(int iLevelId) {

}

void GameManager::resetLevel() {
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;

    auto dispatcher = EventDispatcher::getInstance();

    switch(keyCode) {
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
            
        default:
            break;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();
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
