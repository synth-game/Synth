/*!
 * \file GameManager.cpp
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */
#include "GameManager.h"
#include "core/ActorType.h"
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "FmodAudioPlayer.h"

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

	//TEST ZONE - BEGIN
	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	pBgSprite->setAnchorPoint(Point::ZERO);
	_pBackgroundLayer->addChild(pBgSprite);

	LevelSprite* pLevelSprite = LevelSprite::create("levels/test/bitmask.png");
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_0.png")->getTexture(), Color4B::RED);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_1.png")->getTexture(), Color4B::GREEN);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_2.png")->getTexture(), Color4B::BLUE);
	_pLevelLayer->addChild(pLevelSprite);

	hero = new core::SynthActor(core::ActorType::HERO);
	hero->addComponent(physics::GeometryComponent::create(Point(200.f, 200.f), Size(20.f, 90.f), 0.f, Point(0.f, 0.f)));
	hero->addComponent(physics::MovementComponent::create(Point(20.f, 20.f), Point(0.f, -5.f)));

	physics::CollisionComponent* pHeroColComp = physics::CollisionComponent::create();
	Image* pBitmask = new Image();
	pBitmask->initWithImageFile("levels/test/bitmask.png");
	physics::PhysicCollision* pPhyCol = new physics::PhysicCollision(pBitmask, Point(0, pBitmask->getHeight()));
	pHeroColComp->addPhysicCollision(pPhyCol);
	hero->addComponent(pHeroColComp);

	hero->addComponent(graphics::HeroAnimatedSpriteComponent::create(_pLevelLayer));
	
	FMOD::Channel* channel_green = FmodAudioPlayer::sharedPlayer()->playSound("sound/music/vert_piano.wav", true, 1, 0, 0);
	FmodAudioPlayer::sharedPlayer()->InitMusic();
	//FmodAudioPlayer::sharedPlayer()->playEffect("sound/music/bleu_xylo.wav", true, 1, 0, 1);

	//TEST ZONE - END

	return bTest;
}

void GameManager::update(float fDt) {
	hero->update(fDt);
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(hero->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	//CCLOG("position %2.f, %2.f", pGeometryComponent->getPosition().x, pGeometryComponent->getPosition().y);
}

void GameManager::loadLevel(int iLevelId) {

}

void GameManager::resetLevel() {
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;

    auto dispatcher = EventDispatcher::getInstance();

    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_Q:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(-1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent LEFT");
            dispatcher->dispatchEvent(pEditMoveEvent);
			
            break;
            
        case EventKeyboard::KeyCode::KEY_D:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent RIGHT");
            dispatcher->dispatchEvent(pEditMoveEvent);
			FmodAudioPlayer::sharedPlayer()->StopMusicTrack(FmodAudioPlayer::tracks::green);
            break;
            
        case EventKeyboard::KeyCode::KEY_SPACE:
            //CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/music/blanc_orchestre.wav");
            //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/effects/jump8bit.wav");
            //FmodAudioPlayer::sharedPlayer()->playEffect("sound/effects/jump.wav", false, 1.f, 0.f, 1.f);
			
			
            pJumpEvent = new events::JumpEvent(hero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;
            
        default:
            break;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_Q:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, false);
            dispatcher->dispatchEvent(pEditMoveEvent);
			FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(FmodAudioPlayer::tracks::green);
            break;
        case EventKeyboard::KeyCode::KEY_D:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(-1., 0.), true, false, false);
            dispatcher->dispatchEvent(pEditMoveEvent);
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            /*jumpEvent = new ActorJumpEvent(_hero);
            jumpEvent->_bStart = false;
            dispatcher->dispatchEvent(jumpEvent);*/
            break;
        default:
            break;
	}
}

Color4B GameManager::getLightColor(core::SynthActor* pLight) {
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorsByTag(std::string sTag) {
	std::vector<core::SynthActor*> emptyVec;
	return emptyVec;
}

//void GameManager::onEditMove(EventCustom* pEvent) { 
//	CCLOG("on edit move gm");
//}

}  // namespace game
