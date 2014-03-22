/*!
 * \file InGameMenuLayer.cpp
 * \brief The menu during the game
 * \author Chupee
 * \date 20/03/2014
 */
#include "InGameMenuLayer.h"

#include "events/ResumeGameEvent.h"
#include "events/ExitGameEvent.h"
#include "events/ResetLevelEvent.h"

namespace menu {

InGameMenuLayer::InGameMenuLayer() 
	: Layer()
	, _pBackgroundLayer(nullptr)
	, _pBtnMainMenu(nullptr)
	, _pBtnQuit(nullptr)
	, _pBtnResumeGame(nullptr) 
	, _pBtnRetry(nullptr)
	, _pBtnSelectLevel(nullptr)
	, _pBtnSettings(nullptr) {
}

InGameMenuLayer::~InGameMenuLayer() {
}

InGameMenuLayer* InGameMenuLayer::create() {
	InGameMenuLayer* pRet = new InGameMenuLayer();
	if (pRet != nullptr && pRet->init()) {
		CCLOG("InGameMenuLayer created");
		pRet->autorelease();
	} else {
		CCLOG("InGameMenuLayer created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool InGameMenuLayer::init() {
	bool bRet = Layer::init();

	Point center = Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2);

	Sprite* pBackground = Sprite::create("sprites/pause_menu.png");

	_pBtnResumeGame = MenuItemImage::create("sprites/resume_btn.png", "sprites/resume_btn_selected.png", this, menu_selector(InGameMenuLayer::dispatchResumeGameEvent));
	
	_pBtnRetry = MenuItemImage::create("sprites/restart_btn.png", "sprites/restart_btn_selected.png", this, menu_selector(InGameMenuLayer::dispatchReselLevelEvent));
	_pBtnRetry->setPositionY(0);
	_pBtnQuit = MenuItemImage::create("sprites/quit_btn.png", "sprites/quit_btn_selected.png", this, menu_selector(InGameMenuLayer::dispatchExitGameEvent));

	_pMenuLayer = Menu::create(_pBtnResumeGame, _pBtnRetry, _pBtnQuit, NULL);
	_pMenuLayer->alignItemsVerticallyWithPadding(23.5f);
	_pMenuLayer->setPosition(Point(10.f, -98.5f));
	//_pMenuLayer->setAnchorPoint(Point::ZERO);
	
	addChild(pBackground, 1);
	addChild(_pMenuLayer, 2);
	return bRet;
}

void InGameMenuLayer::onKeyPressed(Event* pEvent) {
}

void InGameMenuLayer::dispatchResumeGameEvent(Object* pSender) {
	events::ResumeGameEvent* pEvent = new events::ResumeGameEvent();
	EventDispatcher::getInstance()->dispatchEvent(pEvent);
	delete pEvent;
}

void InGameMenuLayer::dispatchExitGameEvent(Object* pSender) {
	events::ExitGameEvent* pEvent = new events::ExitGameEvent();
	EventDispatcher::getInstance()->dispatchEvent(pEvent);
	delete pEvent;
}

void InGameMenuLayer::dispatchReselLevelEvent(Object* pSender) {
	events::ResetLevelEvent* pEvent = new events::ResetLevelEvent();
	EventDispatcher::getInstance()->dispatchEvent(pEvent);
	delete pEvent;
}

}  // namespace menu
