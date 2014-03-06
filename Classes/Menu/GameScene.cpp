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
	Point origin = Director::sharedDirector()->getVisibleOrigin();
    Size size = Director::sharedDirector()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
    Point center = Point(size.width/2 + origin.x, size.height/2 + origin.y);

	float playfield_width = size.width * 2.0; // make the x-boundry 2 times the screen width
    float playfield_height = size.height * 2.0; // make the y-boundry 2 times the screen height

	graphics::AnimatedSpriteComponent* pAnimatedSpriteComponent = static_cast<graphics::AnimatedSpriteComponent*>(_pGameLayer->hero->getComponent(graphics::AnimatedSpriteComponent::COMPONENT_TYPE));
	this->runAction(Follow::create(pAnimatedSpriteComponent->getSprite(), Rect( center.x - playfield_width/2, center.y - playfield_height/2 , playfield_width, playfield_height)));

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
