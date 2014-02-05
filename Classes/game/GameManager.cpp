#include "GameManager.h"

namespace Game
{

GameManager::GameManager()
{
}

GameManager::GameManager()
{
}

GameManager* GameManager::create() {
    GameManager* pRet = new GameManager();
    if (pRet != nullptr) {
        CCLOG("GameManager create");
        pRet->autorelease();
    } else {
        CCLOG("GameManager create but delete");
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool GameManager::init() {
    // super init
    if (!Layer::init()) {
        return false;
    }

    // activate key event handling
    setKeyboardEnabled(true);

    // activate update function
    scheduleUpdate();

    // init and add sprites
    _pBackground = Sprite::create("sprites/background.jpg");
    _pBackground->setAnchorPoint(Point(0.f, 0.f));
    this->addChild(_pBackground, 0);

    _pHero = new SynthActor();
    _pHero->addComponent(GeometryComponent::create(Point(300.f,200.f)));
    _pHero->addComponent(MovementComponent::create(Point(0.f, -2.f)));
    _pHero->addComponent(SpriteComponent::create("sprites/sprite_hero.png", this));

    return true;
}

void GameManager::loadLevel(int iLevelId)
{
}

void GameManager::resetLevel()
{
}

void GameManager::update(float fDt) {
    // actors
    _pHero->update(fDt);
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    CCLOG("PRESS");
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    CCLOG("RELEASE");
}

Color4B GameManager::getLightColor(core::SynthActor* pLight)
{
	return 0;
}

vector<SynthActor*> GameManager::getActorByTag(string sTag)
{
	return 0;
}
}  // namespace Game
