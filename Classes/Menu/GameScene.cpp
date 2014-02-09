#include "GameScene.h"

namespace menu {

GameScene::GameScene() 
	: Scene()
	, _pGameLayer(nullptr) 
	, _pMenu(nullptr) 
	, _pDeathEventListener(nullptr) 
	, _pResetLevelEventListener(nullptr)
	, _pPauseGameEventListener(nullptr)
	, _pResumeGameEventListener(nullptr) {

}

GameScene::~GameScene() {
	if (_pGameLayer != nullptr) { delete _pGameLayer; }
	if (_pMenu != nullptr) { delete _pMenu; }
	if (_pDeathEventListener != nullptr) { delete _pDeathEventListener; }
	if (_pResetLevelEventListener != nullptr) { delete _pResetLevelEventListener; }
	if (_pPauseGameEventListener != nullptr) { delete _pPauseGameEventListener; }
	if (_pResumeGameEventListener != nullptr) { delete _pResumeGameEventListener; }
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

	//init listeners
	//TO DO

	return bTest;
}

void GameScene::launchLevel(int iLevelID) {

}

void GameScene::onDeathEvent(Event* pEvent) {

}

void GameScene::onResetLevelEvent(Event* pEvent) {

}

void GameScene::onPauseGameEvent(Event* pEvent) {

}

void GameScene::onResumeGameEvent(Event* pEvent) {

}

}  // namespace menu
