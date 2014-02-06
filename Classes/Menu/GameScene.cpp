#include "GameScene.h"

namespace menu
{

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

GameScene* GameScene::create()
{
	return 0;
}

bool GameScene::init()
{
	return false;
}

void GameScene::launchLevel(int iLevelID)
{
}

void GameScene::onDeathEvent(Event* pEvent)
{
}

void GameScene::onResetLevelEvent(Event* pEvent)
{
}

void GameScene::onPauseGameEvent(Event* pEvent)
{
}

void GameScene::onResumeGameEvent(Event* pEvent)
{
}
}  // namespace menu
