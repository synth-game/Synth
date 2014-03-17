/*!
 * \file TitleScreenScene.cpp
 * \brief The title screen of the game
 * \author Chupee
 * \date 17/03/2014
 */
#include "TitleScreenScene.h"
#include "core/SynthManager.h"

#include "events/NewGameEvent.h"

namespace menu {

TitleScreenScene::TitleScreenScene()
	: Scene()
	, _pButtonLayer(nullptr) 
	, _pBackgroundLayer(nullptr) 
	, _pMenuLayer(nullptr)
	, _pSettingsLayer(nullptr) 
	, _pBtnNewGame(nullptr) 
	, _pBtnPlay(nullptr)
	, _pBtnSelectLevel(nullptr)
	, _pBtnCredits(nullptr)
	, _pBtnQuit(nullptr)
	, _pBtnSettings(nullptr)
	, _iSelectedButtonID(0)
	, _iButtonCount(0) {
}

TitleScreenScene::~TitleScreenScene() {
}

TitleScreenScene* TitleScreenScene::create(std::string sBgFileName, bool bIsThereGame) {
	TitleScreenScene* pRet = new TitleScreenScene();
	if (pRet != nullptr && pRet->init()) {
		CCLOG("TitleScreenScene created");
		pRet->autorelease();
	} else {
		CCLOG("TitleScreenScene created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool TitleScreenScene::init() {

	bool bRet = Scene::init();

	Point center = Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2);

	initListeners();

	_pBackgroundLayer = Layer::create();

	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	_pBackgroundLayer->addChild(pBgSprite);
	_pBackgroundLayer->setPosition(center);
	

	_pBtnPlay = MenuItemFont::create("Jouer", this, menu_selector(TitleScreenScene::dispatchNewGameEvent));
	//_pBtnQuit = MenuItemFont::create("Quitter",  CC_CALLBACK_0(TitleScreenScene::dispatchQuitEvent, this));
	//_pMenuLayer->addChild(_pBtnQuit, 10);
	_pMenuLayer = Menu::create(_pBtnPlay, NULL);
	_pMenuLayer->setPosition(center);
	
	Scene::addChild(_pBackgroundLayer, 0);
	Scene::addChild(_pMenuLayer, 1);


	return bRet;
}

void TitleScreenScene::dispatchNewGameEvent(Object* pSender) {
	events::NewGameEvent* pNewGameEvent = new events::NewGameEvent();
	EventDispatcher::getInstance()->dispatchEvent(pNewGameEvent);
}

void TitleScreenScene::dispatchQuitEvent() {
	
}

void TitleScreenScene::initListeners() {
	//_pDeathEventListener = cocos2d::EventListenerCustom::create(events::DeathEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onDeathEvent, this));

	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pDeathEventListener, 1);
}

void TitleScreenScene::onKeyPressed(Event* pEvent) {
	CCLOG("Title screen : KEY PRESSED");
}

}  // namespace menu
