/*!
 * \file SynthManager.cpp
 * \brief Main manager, the entry point of our program
 * \author Jijidici
 * \date 09/02/2014
 */
#include "SynthManager.h"

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
	_pGameScene = menu::GameScene::create();

	//init listeners

	//setup initial scene
	Director::getInstance()->runWithScene(_pGameScene);
}

void SynthManager::onNewGameEvent(EventCustom* event) {

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
