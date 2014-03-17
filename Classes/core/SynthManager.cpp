/*!
 * \file SynthManager.cpp
 * \brief Main manager, the entry point of our program
 * \author Jijidici
 * \date 09/02/2014
 */
#include "SynthManager.h"
#include "graphics/GraphicManager.h"
#include "sounds/SoundManager.h"

#include "events/NewGameEvent.h"

namespace core {

SynthManager::SynthManager() 
	: _pTitleScreenScene(nullptr) 
	, _pCreditsScene(nullptr)
	, _pGameScene(nullptr)
	, _pSelectLevelScene(nullptr) 
	, _pNewGameEventListener(nullptr)
	, _pContinueGameEventListener(nullptr) 
	, _pOpenTitleScreenEventListener(nullptr)
	, _pOpenCreditsEventListener(nullptr)
	, _pOpenSelectLevelScreenEventListener(nullptr)
	, _pLoadSelectedLevelEventListener(nullptr) 
	, _pExitGameEventListener(nullptr) {
	
}

SynthManager::~SynthManager() {
	
}

void SynthManager::init() {
    //init scenes
	_pTitleScreenScene = menu::TitleScreenScene::create("sprites/decor.jpg", false);

	//init managers
	graphics::GraphicManager* gm = graphics::GraphicManager::getInstance();
	sounds::SoundManager* sm = sounds::SoundManager::getInstance();

	//init listeners
	_pNewGameEventListener = EventListenerCustom::create(events::NewGameEvent::EVENT_NAME, CC_CALLBACK_1(SynthManager::onNewGameEvent, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pNewGameEventListener, 1);

	//setup initial scene
	Director::getInstance()->runWithScene(_pTitleScreenScene);
}

void SynthManager::onNewGameEvent(EventCustom* event) {
	_pGameScene = menu::GameScene::create();
	Director::getInstance()->replaceScene(_pGameScene);
}

void SynthManager::onContinueGameEvent(EventCustom* event) {

}

void SynthManager::onOpenTitleScreenEvent(EventCustom* event) {

}

void SynthManager::onOpenCreditsEvent(EventCustom* event) {

}

void SynthManager::onOpenSelectLevelScreenEvent(EventCustom* event) {

}

void SynthManager::onLoadSelectedLevelEvent(EventCustom* event) {

}

void SynthManager::onExitGameEvent(EventCustom* event) {

}

}  // namespace core
