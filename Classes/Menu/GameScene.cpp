#include "cocos2d.h"
#include "GameScene.h"
#include "graphics/AnimatedSpriteComponent.h"
#include "events/DeathEvent.h"
#include "Events/WinEvent.h"
#include "events/ResetLevelEvent.h"
#include "events/PauseGameEvent.h"
#include "events/ResumeGameEvent.h"
#include "core/SynthConfig.h"
#include "sounds/SoundManager.h"

namespace menu {

GameScene::GameScene() 
	: Scene()
	, _pGameLayer(nullptr) 
	, _pMenu(nullptr) 
	, _pDeathEventListener(nullptr) 
	, _pWinEventListener(nullptr) 
	, _pResetLevelEventListener(nullptr)
	, _pPauseGameEventListener(nullptr)
	, _pResumeGameEventListener(nullptr) {

}

GameScene::~GameScene() {
	EventDispatcher::getInstance()->removeEventListener(_pDeathEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pWinEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pResetLevelEventListener);
	//EventDispatcher::getInstance()->removeEventListener(_pPauseGameEventListener);
	//EventDispatcher::getInstance()->removeEventListener(_pResumeGameEventListener);
}

GameScene* GameScene::create() {
	GameScene* pRet = new GameScene();
	if (pRet != nullptr && pRet->init()) {
		CCLOG("GameScene created");
		pRet->autorelease();
	} else {
		CCLOG("GameScene created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameScene::init() {
	bool bTest = true;

	//init scene
	bTest = Scene::init();

	//create layers
	_pGameLayer = game::GameManager::create();
	Scene::addChild(_pGameLayer);

	// Camera
	initCamera();

	//init listeners
	_pDeathEventListener = cocos2d::EventListenerCustom::create(events::DeathEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onDeathEvent, this));
	_pWinEventListener = cocos2d::EventListenerCustom::create(events::WinEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onWinEvent, this));
	_pResetLevelEventListener = cocos2d::EventListenerCustom::create(events::ResetLevelEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onResetLevelEvent, this));
	//_pPauseGameEventListener = cocos2d::EventListenerCustom::create(events::PauseGameEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onPauseGameEvent, this));
	//_pResumeGameEventListener = cocos2d::EventListenerCustom::create(events::ResumeGameEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onResumeGameEvent, this));

	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pDeathEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pWinEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pResetLevelEventListener, 1);
	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pPauseGameEventListener, 1);
	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pResumeGameEventListener, 1);

	return bTest;
}

void GameScene::initCamera() {
	float playfield_width = _pGameLayer->getLevelSprite()->getContentSize().width;
    float playfield_height = _pGameLayer->getLevelSprite()->getContentSize().height;
	Rect boundaries =  Rect( 0.f, 0.f , playfield_width, playfield_height);

	graphics::AnimatedSpriteComponent* pAnimatedSpriteComponent = static_cast<graphics::AnimatedSpriteComponent*>(_pGameLayer->getActorsByType(core::ActorType::HERO)[0]->getComponent(graphics::AnimatedSpriteComponent::COMPONENT_TYPE));
	this->stopAllActions();
	this->runAction(Follow::create(pAnimatedSpriteComponent->getSprite(), boundaries));
}

void GameScene::launchLevel(int iLevelID) {

}

void GameScene::onDeathEvent(Event* pEvent) {
	events::DeathEvent* deathEvent = static_cast<events::DeathEvent*>(pEvent);
	sounds::SoundManager::getInstance()->stopEffects();
	_pGameLayer->resetLevel();
	initCamera();
}

void GameScene::onWinEvent(Event* pEvent) {
	events::WinEvent* winEvent = static_cast<events::WinEvent*>(pEvent);
	int savedLevelIndex = core::SynthConfig::getInstance()->getCurrentLevelIndex();
	if(savedLevelIndex < _pGameLayer->getCurrentLevelIndex() + 1) {
		core::SynthConfig::getInstance()->saveCurrentLevelIndex(_pGameLayer->getCurrentLevelIndex() + 1);
	}
	_pGameLayer->nextLevel();
	initCamera();
}

void GameScene::onResetLevelEvent(Event* pEvent) {
	events::ResetLevelEvent* resetLevelEvent = static_cast<events::ResetLevelEvent*>(pEvent);
	_pGameLayer->resetLevel();
	initCamera();
}

void GameScene::onPauseGameEvent(Event* pEvent) {

}

void GameScene::onResumeGameEvent(Event* pEvent) {

}

}  // namespace menu
