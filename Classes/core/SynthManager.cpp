#include "SynthManager.h"

namespace Core
{

SynthManager::SynthManager()
{
}

SynthManager::~SynthManager()
{
}

void SynthManager::init() {
    // create and use the gamescene
    _pGameScene = Scene::create();
    // Singleton de Cocos2dx qui permet de faire des trucs (voir doc)
    Director::getInstance()->runWithScene(_pGameScene);

    // init GameManager
    _pGameManager = GameManager::create();
    // Node::addChild() de Cocos2dx qui ajoute un objet à un Layer
    _pGameScene->addChild(_pGameManager);

    _pGameManager->init();
}

void SynthManager::onNewGameEvent(EventCustom* event)
{
}

void SynthManager::onContinueGameEvent(EventCustom* event)
{
}

void SynthManager::onOpenSelectLevelScreenEvent(EventCustom* event)
{
}

void SynthManager::onOpenSettingsEvent(EventCustom* event)
{
}

void SynthManager::onOpenCreditsEvent(EventCustom* event)
{
}

void SynthManager::onExitGameEvent(EventCustom* event)
{
}

void SynthManager::onOpenTitleScreenEvent(EventCustom* event)
{
}

void SynthManager::onLoadSelectedLevelEvent(EventCustom* event)
{
}
}  // namespace Core
