/*!
 * \file GameManager.cpp
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */
#include "GameManager.h"
#include "core/SynthActor.h"
#include "physics/GeometryComponent.h"
#include "graphics/GraphicManager.h"
#include "graphics/SpriteComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"

namespace game {

GameManager::GameManager() 
	: Layer() 
	, _iCurrentLevelId(-1)
	, _fTimeSinceLevelStart(0.f) 
	, _levelActors() 
	, _triggers()
	, _pLevelSprite(nullptr) 
	, _pBackgroundLayer(nullptr) 
	, _pIntermediarLayer(nullptr)
	, _pLevelLayer(nullptr) 
	, _pSkinningLayer(nullptr) 
	, _pSubtitlesLayer(nullptr) 
	, _pParallaxManager(nullptr) {

}

GameManager::~GameManager() {
	_levelActors.clear();
	_triggers.clear();
}

GameManager* GameManager::create() {
	GameManager* pRet = new GameManager();
	if (pRet != nullptr && pRet->init()) {
		CCLOG("GameManager created");
		pRet->autorelease();
	} else {
		CCLOG("GameManager created but deleted");
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameManager::init() {
    bool bTest = true;

	//init Layer
	bTest = Layer::init();

	// activate key event handling
	setKeyboardEnabled(true);

	// activate update function
	scheduleUpdate();

	//init layers
	_pBackgroundLayer = Layer::create();
	_pIntermediarLayer = Layer::create();
	_pLevelLayer = Layer::create();
	_pSkinningLayer = Layer::create();
	_pSubtitlesLayer = Layer::create();
	
	_pParallaxManager = ParallaxNode::create();
	_pParallaxManager->addChild(_pBackgroundLayer, 1, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pIntermediarLayer, 2, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pLevelLayer, 3, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSkinningLayer, 4, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSubtitlesLayer, 5, Point(1.f, 1.f), Point(0.f, 0.f));
	Layer::addChild(_pParallaxManager);

	// Background
	graphics::GraphicManager* graphicManager = graphics::GraphicManager::getInstance();
	Sprite* pBgSprite = graphicManager->createSprite("sprites/decor.jpg");
	_pBackgroundLayer->addChild(pBgSprite, 0, 42);

	// test geometryComponent
	core::SynthActor actor = core::SynthActor("CAKE");
	actor.addComponent(physics::GeometryComponent::create(Point(100.f,100.f), Size(16,16), 0.f, Point(0,0)));
	// test spriteComponent
	actor.addComponent(graphics::SpriteComponent::create("sprites/cake.png", _pLevelLayer));
	// test animatedspritecomponent
	core::SynthActor animatedActor = core::SynthActor("HERO");
	animatedActor.addComponent(physics::GeometryComponent::create(Point(300.f,300.f), Size(48,100), 0.f, Point(0,0)));
	animatedActor.addComponent(graphics::HeroAnimatedSpriteComponent::create(_pLevelLayer));
	return bTest;
}

void GameManager::update(float fDt) {
 
}

void GameManager::loadLevel(int iLevelId) {

}

void GameManager::resetLevel() {
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {

}

Color4B GameManager::getLightColor(core::SynthActor* pLight) {
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorsByTag(std::string sTag) {
	std::vector<core::SynthActor*> emptyVec;
	return emptyVec;
}

}  // namespace game
