/* *****************************************************
 *		GameManager.cpp - @ Jeremie Defaye - 29/01/14
 ***************************************************** */

#include "game/GameManager.h"
#include "graphics/SpriteComponent.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"

USING_NS_CC;

GameManager::GameManager() 
	: Layer()
	, _pBackground(nullptr)
	, _pHero(nullptr) {

}

GameManager::~GameManager() {

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