#include "GameManager.h"

namespace game
{

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

GameManager* GameManager::create() {
    return nullptr;
}

bool GameManager::init() {
    return false;
}

void GameManager::loadLevel(int iLevelId)
{
}

void GameManager::resetLevel()
{
}

void GameManager::update(float fDt) {
 
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {

}

Color4B GameManager::getLightColor(core::SynthActor* pLight)
{
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorByTag(std::string sTag)
{
	std::vector<core::SynthActor*> emptyVec;
	return emptyVec;
}
}  // namespace game
