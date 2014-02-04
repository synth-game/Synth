#include "GameManager.h"

namespace Game
{

GameManager::GameManager()
{
}

GameManager::GameManager()
{
}

GameManager* GameManager::create()
{
	return 0;
}

void GameManager::init()
{
}

void GameManager::loadLevel(int iLevelId)
{
}

void GameManager::resetLevel()
{
}

void GameManager::update(int float fDt)
{
}

void GameManager::onKeyPressed(Event* pEvent)
{
}

void GameManager::onKeyReleased(Event* pEvent)
{
}

Color4B GameManager::getLightColor(Core::SynthActor* pLight)
{
	return 0;
}

vector<SynthActor*> GameManager::getActorByTag(string sTag)
{
	return 0;
}
}  // namespace Game
