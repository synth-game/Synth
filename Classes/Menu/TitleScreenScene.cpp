/*!
 * \file TitleScreenScene.cpp
 * \brief The title screen of the game
 * \author Chupee
 * \date 17/03/2014
 */
#include "TitleScreenScene.h"
#include "core/SynthManager.h"
#include "sounds/SoundManager.h"

#include "events/NewGameEvent.h"
#include "events/ExitGameEvent.h"

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
	//EventDispatcher::getInstance()->removeEventListener(_pDeathEventListener);
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
	Point menuCoord = Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2 - 108);

	initListeners();

	sounds::SoundManager::getInstance()->updateMusics(Color4B::BLUE);
	sounds::SoundManager::getInstance()->updateMusics(Color4B::GREEN);
	sounds::SoundManager::getInstance()->updateMusics(Color4B::RED);

	_pBackgroundLayer = Layer::create();

	Sprite* pBgSprite = Sprite::create("sprites/main_menu.png");
	_pBackgroundLayer->addChild(pBgSprite);
	_pBackgroundLayer->setPosition(center);

	_pBtnPlay = MenuItemImage::create("sprites/play_btn.png", "sprites/play_btn_selected.png", this, menu_selector(TitleScreenScene::dispatchNewGameEvent));
	_pBtnQuit = MenuItemImage::create("sprites/quit_btn.png", "sprites/quit_btn_selected.png", this, menu_selector(TitleScreenScene::dispatchExitGameEvent));

	_pMenuLayer = Menu::create(_pBtnPlay, _pBtnQuit, NULL);
	_pMenuLayer->alignItemsVerticallyWithPadding(28.f);
	_pMenuLayer->setPosition(menuCoord);
	
	Scene::addChild(_pBackgroundLayer, 0);
	Scene::addChild(_pMenuLayer, 2);

	return bRet;
}

void TitleScreenScene::dispatchNewGameEvent(Object* pSender) {
	events::NewGameEvent* pNewGameEvent = new events::NewGameEvent();
	EventDispatcher::getInstance()->dispatchEvent(pNewGameEvent);
	delete pNewGameEvent;
}

void TitleScreenScene::dispatchExitGameEvent(Object* pSender) {
	events::ExitGameEvent* pExitGameEvent = new events::ExitGameEvent();
	EventDispatcher::getInstance()->dispatchEvent(pExitGameEvent);
	delete pExitGameEvent;
}

void TitleScreenScene::initListeners() {
	//_pDeathEventListener = cocos2d::EventListenerCustom::create(events::DeathEvent::EVENT_NAME, CC_CALLBACK_1(GameScene::onDeathEvent, this));

	//EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pDeathEventListener, 1);
}

void TitleScreenScene::onKeyPressed(Event* pEvent) {
	CCLOG("Title screen : KEY PRESSED");
}

}  // namespace menu
