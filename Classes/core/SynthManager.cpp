/* *****************************************************
 *		SynthManager.cpp - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#include "core/SynthManager.h"

USING_NS_CC;

SynthManager::SynthManager()
	: _pGameScene(nullptr)
	, _pGameManager(nullptr) {

}

SynthManager::~SynthManager() {
	if(_pGameScene != nullptr) delete _pGameScene;
}

void SynthManager::init() {
	// create and use the gamescene
	_pGameScene = Scene::create();
	Director::getInstance()->runWithScene(_pGameScene);

	// init GameManager
	_pGameManager = GameManager::create();
	_pGameScene->addChild(_pGameManager);

	_pGameManager->init();
}