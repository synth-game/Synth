#include "cocos2d.h"
#include "GameScene.h"
#include "graphics/AnimatedSpriteComponent.h"

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
	float playfield_width = _pGameLayer->getLevelLayer()->getChildByTag(42)->getContentSize().width;
    float playfield_height = _pGameLayer->getLevelLayer()->getChildByTag(42)->getContentSize().height;
	Rect boundaries =  Rect( 0.f, 0.f , playfield_width, playfield_height);

	graphics::AnimatedSpriteComponent* pAnimatedSpriteComponent = static_cast<graphics::AnimatedSpriteComponent*>(_pGameLayer->hero->getComponent(graphics::AnimatedSpriteComponent::COMPONENT_TYPE));
	this->runAction(Follow::create(pAnimatedSpriteComponent->getSprite(), boundaries));

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
