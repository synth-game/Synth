/*!
 * \file GameManager.cpp
 * \brief Manager of the entire game
 * \author Jijidici
 * \date 09/02/2014
 */

#include "GameManager.h"
#include "game/LevelFactory.h"
#include "game/LightMap.h"
#include "game/LightAttrComponent.h"
#include "game/SwitchableComponent.h"
#include "core/ActorType.h"
#include "core/SynthConfig.h"
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/FlyMovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/BounceCollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "physics/FollowMovementComponent.h"
#include "physics/StickMovementComponent.h"
#include "physics/StickCollisionComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "graphics/FireflyAnimatedSpriteComponent.h"
#include "graphics/GraphicManager.h"
#include "game/NodeOwnerComponent.h"
#include "system/IOManager.h"
#include "sounds/SoundType.h"
#include "sounds/VoiceManager.h"

#include "events/PauseGameEvent.h"
#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeTargetEvent.h"
#include "events/WinEvent.h"
#include "events/DeathEvent.h"
#include "events/ResetLevelEvent.h"
#include "events/EnterLightEvent.h"
#include "events/ToggleLightEvent.h"
#include "events/PauseGameEvent.h"
#include "events/ResumeGameEvent.h"

#include "FmodAudioPlayer.h"


namespace game {

GameManager::GameManager() 
	: Layer() 
	, _iCurrentLevelId(-1)
	, _fTimeSinceLevelStart(0.f)
	, _levelsName()
	, _levelActors() 
	, _triggers()
	, _bResetRequested(false)
	, _bNextRequested(false)
	, _bChangeColor(false)
	, _currentColor(0, 0, 0, 0)
	, _previousColor(0, 0, 0, 0)
	, _pLevelSprite(nullptr) 
	, _pLightMap(nullptr)
	, _pBackgroundLayer(nullptr) 
	, _pIntermediarLayer(nullptr)
	, _pLevelLayer(nullptr) 
	, _pSkinningLayer(nullptr) 
	, _pSubtitlesLayer(nullptr) 
	, _pParallaxManager(nullptr)
	, _pSavedMovementComp(nullptr)
	, _pSavedPhysicColl(nullptr)
	, _pEnterLightListener(nullptr)
	, _pPauseEventListener(nullptr)
	, _pResumeEventListener(nullptr)
	, _keyPressedCode()
	, _bIsPaused(false) {

}

GameManager::~GameManager() {
	_levelActors.clear();
	_triggers.clear();

	EventDispatcher::getInstance()->removeEventListener(_pEnterLightListener);
	EventDispatcher::getInstance()->removeEventListener(_pPauseEventListener);
	EventDispatcher::getInstance()->removeEventListener(_pResumeEventListener);
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

	setKeyboardEnabled(true);
	scheduleUpdate();

	//init layers
	_pBackgroundLayer = Layer::create();
	_pIntermediarLayer = Layer::create();
	_pLevelLayer = Layer::create();
	_pSkinningLayer = Layer::create();
	_pSubtitlesLayer = Layer::create();
	
	_pParallaxManager = ParallaxNode::create();
	_pParallaxManager->addChild(_pBackgroundLayer, 1, Point(0.7f, 0.7f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pIntermediarLayer, 2, Point(0.8f, 0.8f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pLevelLayer, 3, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSkinningLayer, 4, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSubtitlesLayer, 5, Point(1.f, 1.f), Point(0.f, 0.f));
	Layer::addChild(_pParallaxManager);

	// init listeners
	_pEnterLightListener = EventListenerCustom::create(events::EnterLightEvent::EVENT_NAME, CC_CALLBACK_1(GameManager::onEnterLight, this));
	_pPauseEventListener = EventListenerCustom::create(events::PauseGameEvent::EVENT_NAME, CC_CALLBACK_1(GameManager::onPause, this));
	_pResumeEventListener = EventListenerCustom::create(events::ResumeGameEvent::EVENT_NAME, CC_CALLBACK_1(GameManager::onResume, this));
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEnterLightListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pPauseEventListener, 1);
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pResumeEventListener, 1);

	// init levels
	_iCurrentLevelId = core::SynthConfig::getInstance()->getCurrentLevelIndex();
	CCASSERT(_iCurrentLevelId >= 0, "ERROR WITH THE CONFIG FILE WHILE LOADING LEVEL");

	tinyxml2::XMLDocument* pLevelsDoc = synthsystem::IOManager::getInstance()->loadXML("xml/levels.xml");
	tinyxml2::XMLElement* pGameElt = pLevelsDoc->FirstChildElement("game");
	tinyxml2::XMLElement* pLevelElt = pGameElt->FirstChildElement("level");
	while(pLevelElt != nullptr) {
		_levelsName.push_back(pLevelElt->Attribute("name"));

		pLevelElt = pLevelElt->NextSiblingElement("level");
	}
	delete pLevelsDoc;

	//TEST ZONE - BEGIN
	loadLevel(_levelsName[_iCurrentLevelId]);

	//TEST ZONE - END

	return bTest;

	// Init sounds ids
	stepsSoundId = -1; //-1 >> not playing
}

void GameManager::update(float fDt) {
	core::SynthActor* pHero = nullptr;
	pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::update : There is no HERO actor");
	physics::GeometryComponent* pGeometryComp = dynamic_cast<physics::GeometryComponent*>(pHero->getComponent(physics::GeometryComponent::COMPONENT_TYPE));

	CCASSERT(pGeometryComp != nullptr, "HERO actor needs a GeometryComponent");
	if(_triggers["WIN"].containsPoint(pGeometryComp->getPosition())) {
		_bNextRequested = true;
	}

	for (map<std::string,Rect>::iterator trigger=_triggers.begin(); trigger!=_triggers.end(); ++trigger) {
		if (trigger->first !="WIN"){
			if(trigger->second.containsPoint(pGeometryComp->getPosition())) {
				sounds::VoiceManager::getInstance()->playNextVoice();
				_triggers.erase(trigger);
				break;
			}
		}
	}
	
	// check if the hero is alive - inside the level
	if(!_pLevelSprite->getTextureRect().containsPoint(pGeometryComp->getPosition())) {
		_bResetRequested = true;
	}

	if(!isPaused()) {
		for (auto actor : _levelActors) {
			actor->update(fDt);
		}
	}
	

	// manage light change
	if(_bChangeColor) {
		if (_currentColor == Color4B::RED) {
			_bResetRequested = true;
		} else {
			// remove previous component
			core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
			physics::MovementComponent* pPrevMovementComp = dynamic_cast<physics::MovementComponent*>(pHero->getComponent(physics::MovementComponent::COMPONENT_TYPE));
			physics::CollisionComponent* pPrevCollisionComp = dynamic_cast<physics::CollisionComponent*>(pHero->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
			Point currentSpeed;
			Point currentDirection;
			if(pPrevMovementComp != nullptr && pPrevCollisionComp != nullptr) {
				currentSpeed = pPrevMovementComp->getSpeed();
				currentDirection = pPrevMovementComp->getDirection();
				pHero->removeComponent(physics::MovementComponent::COMPONENT_TYPE);
				pHero->removeComponent(physics::CollisionComponent::COMPONENT_TYPE);
			}

			if (_currentColor == Color4B::BLUE) {
				CCLOG("GameManager::onEnterLight : You can jump higher !");
				physics::MovementComponent* pMovementComp = physics::MovementComponent::create(_pSavedMovementComp->getAcceleration(), _pSavedMovementComp->getGravity(), _pSavedMovementComp->getLowGravityFactor(), _pSavedMovementComp->getHighGravityFactor());
				pMovementComp->setSpeed(currentSpeed);
				pMovementComp->setDirection(currentDirection);
				pMovementComp->setGravity(_pSavedMovementComp->getGravity()*_pSavedMovementComp->getLowGravityFactor());
				physics::CollisionComponent* pCollisionComp = physics::CollisionComponent::create();
				pCollisionComp->addPhysicCollision(_pSavedPhysicColl);
				pHero->addComponent(pMovementComp);
				pHero->addComponent(pCollisionComp);
			} else if (_currentColor == Color4B::MAGENTA) {
				CCLOG("GameManager::onEnterLight : You can't jump as high as usually :( ");
				physics::MovementComponent* pMovementComp = physics::MovementComponent::create(_pSavedMovementComp->getAcceleration(), _pSavedMovementComp->getGravity(), _pSavedMovementComp->getLowGravityFactor(), _pSavedMovementComp->getHighGravityFactor());
				pMovementComp->setSpeed(currentSpeed);
				pMovementComp->setDirection(currentDirection);
				pMovementComp->setGravity(_pSavedMovementComp->getGravity()*_pSavedMovementComp->getHighGravityFactor());
				physics::CollisionComponent* pCollisionComp = physics::CollisionComponent::create();
				pCollisionComp->addPhysicCollision(_pSavedPhysicColl);
				pHero->addComponent(pMovementComp);
				pHero->addComponent(pCollisionComp);
			} else if (_currentColor == Color4B::GREEN) {
				CCLOG("GameManager::onEnterLight : You bounce on the floor ! Awww yeah ! ");
				physics::MovementComponent* pMovementComp = physics::MovementComponent::create(_pSavedMovementComp->getAcceleration(), _pSavedMovementComp->getGravity(), _pSavedMovementComp->getLowGravityFactor(), _pSavedMovementComp->getHighGravityFactor());
				pMovementComp->setSpeed(currentSpeed);
				pMovementComp->setDirection(currentDirection);
				physics::BounceCollisionComponent* pCollisionComp = physics::BounceCollisionComponent::create();
				pCollisionComp->addPhysicCollision(_pSavedPhysicColl);
				pHero->addComponent(pMovementComp);
				pHero->addComponent(pCollisionComp);
			}else if (_currentColor == Color4B::YELLOW) {
				CCLOG("GameManager::onEnterLight : You are now a sticky girl ! ");
				physics::StickMovementComponent* pStickMovementComponent = physics::StickMovementComponent::create(_pSavedMovementComp->getAcceleration(), _pSavedMovementComp->getGravity());
				pStickMovementComponent->setSpeed(currentSpeed);
				pStickMovementComponent->setDirection(currentDirection);
				physics::StickCollisionComponent* pStickCollisionComponent = physics::StickCollisionComponent::create();
				pStickCollisionComponent->addPhysicCollision(_pSavedPhysicColl);
				pHero->addComponent(pStickMovementComponent);
				pHero->addComponent(pStickCollisionComponent);
			} else {
				CCLOG("GameManager::onEnterLight : Out of any light");
				physics::MovementComponent* pMovementComp = physics::MovementComponent::create(_pSavedMovementComp->getAcceleration(), _pSavedMovementComp->getGravity(), _pSavedMovementComp->getLowGravityFactor(), _pSavedMovementComp->getHighGravityFactor());
				pMovementComp->setSpeed(currentSpeed);
				pMovementComp->setDirection(currentDirection);
				physics::CollisionComponent* pCollisionComp = physics::CollisionComponent::create();
				pCollisionComp->addPhysicCollision(_pSavedPhysicColl);
				pHero->addComponent(pMovementComp);
				pHero->addComponent(pCollisionComp);
			}
		}

		_bChangeColor = false;
		_previousColor = _currentColor;
	}

	FmodAudioPlayer::sharedPlayer()->Update(fDt);

	// manage resets (death or win)
	if(_bNextRequested) {
		CCLOG("GameManager::update : YOU WIN");
		events::WinEvent* pWinEvent = new events::WinEvent();
		EventDispatcher::getInstance()->dispatchEvent(pWinEvent);
		delete pWinEvent;
		_bNextRequested = false;
	}
	else if(_bResetRequested) {
		CCLOG("GameManager::update : YOU DIE !");
		events::DeathEvent* pDeathEvent = new events::DeathEvent();
		EventDispatcher::getInstance()->dispatchEvent(pDeathEvent);
		delete pDeathEvent;
		_bResetRequested = false;
	}
}

void GameManager::loadLevel(/*int iLevelId*/std::string level) {
    CCLOG("GameManager::loadLevel : LOAD LEVEL");
	// Build background
	Sprite* pBgSprite = Sprite::create(("levels/"+level+"/background.jpg").c_str());
	pBgSprite->setAnchorPoint(Point::ZERO);
	_pBackgroundLayer->addChild(pBgSprite);

	// Build skinning
	Sprite* pSknSprite = Sprite::create(("levels/"+level+"/skinning.png").c_str());
	pSknSprite->setAnchorPoint(Point::ZERO);
	_pSkinningLayer->addChild(pSknSprite);

	// Build actors
	_levelActors = LevelFactory::getInstance()->buildActors(level, _pLevelLayer);

	// Build triggers
	_triggers = LevelFactory::getInstance()->buildTriggers(level);

	// Display debug rectangle for triggers
	for (std::map<std::string, Rect>::iterator it = _triggers.begin(); it != _triggers.end(); ++it) {
		Sprite* rect = Sprite::create("levels/test/rect.png");
		rect->setPosition(it->second.origin);
		rect->setAnchorPoint(Point(0,0));
		rect->setScaleX(it->second.size.width/rect->getContentSize().width);
		rect->setScaleY(it->second.size.height/rect->getContentSize().height);
		_pLevelLayer->addChild(rect, 50);
	}

	// Build LevelSprite and LightMap
	_pLevelSprite = LevelFactory::getInstance()->buildLevelSprite(level, getActorsByType(core::ActorType::LIGHT));
	_pLevelLayer->addChild(_pLevelSprite, 0);
	if (_pLightMap == nullptr) {
		_pLightMap = LevelFactory::getInstance()->buildLightMap(level);
	}

	// Add lightswitches to levelsprite so that it can draw it
	for (auto actor : _levelActors) {
		if (actor->getActorType() == core::ActorType::LIGHTSWITCH) {
			physics::GeometryComponent* pLSGeometryComp = static_cast<physics::GeometryComponent*>(actor->getComponent("GeometryComponent"));
			if (pLSGeometryComp != nullptr) {
				_pLevelSprite->addLightSwitch(pLSGeometryComp);
			}
		}
	}

	// Initialize the LightCollision of the HERO actor
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	physics::CollisionComponent* pCollisionComp = dynamic_cast<physics::CollisionComponent*>(pHero->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
	pCollisionComp->addLightCollision(game::LevelFactory::getInstance()->buildLightsCollision(_pLightMap, getActorsByType(core::ActorType::LIGHT)));


	// Load the correct voices for the level
	sounds::VoiceManager::getInstance()->init(level);

	// Initialized saved data
	physics::MovementComponent* pMovementComp = dynamic_cast<physics::MovementComponent*>(pHero->getComponent(physics::MovementComponent::COMPONENT_TYPE));
	_pSavedMovementComp = physics::MovementComponent::create(pMovementComp->getAcceleration(), pMovementComp->getGravity(), pMovementComp->getLowGravityFactor(), pMovementComp->getHighGravityFactor());
	_pSavedMovementComp->retain();
	_pSavedPhysicColl = pCollisionComp->getPhysicCollision();

}

void GameManager::clearLevel() {
	CCLOG("GameManager::clearLevel : CLEAR LEVEL");
	for(auto obj : _levelActors) {
		obj->removeAllComponents();
		obj->removeFromParent();
		delete obj;
		obj = nullptr;
	}
	_levelActors.clear();
	_triggers.clear();

	if(_pSavedPhysicColl != nullptr) {
		delete _pSavedPhysicColl;
		_pSavedPhysicColl = nullptr;
	}
	if(_pSavedMovementComp != nullptr) {
		_pSavedMovementComp->release();
		_pSavedMovementComp = nullptr;
	}

	_pBackgroundLayer->removeAllChildren();
	_pIntermediarLayer->removeAllChildren();
	_pLevelLayer->removeAllChildren();

	_pLevelSprite = nullptr;
	if (_bNextRequested) {
		delete _pLightMap;
		_pLightMap = nullptr;
	}

	_pSkinningLayer->removeAllChildren();
	_pSubtitlesLayer->removeAllChildren();

	graphics::GraphicManager::getInstance()->reset();

}

void GameManager::resetLevel() {
	CCLOG("GameManager::resetLevel : Clear and reload level");
	_bResetRequested = true;
	clearLevel();
	loadLevel(_levelsName[_iCurrentLevelId]);
}

void GameManager::nextLevel() {
	CCLOG("GameManager::nextLevel : Clear and load next level");
	_bNextRequested = true;
	clearLevel();
	loadLevel(_levelsName[++_iCurrentLevelId]);
}

void GameManager::onEnterLight(EventCustom* pEvent) {
	CCLOG("GameManager::onEnterLight : You just entered a light");
	events::EnterLightEvent* enterLightEvent = static_cast<events::EnterLightEvent*>(pEvent);

	_currentColor = enterLightEvent->getLightingColor();
	_bChangeColor = true;
}

void GameManager::onPause(EventCustom* pEvent) {
	_bIsPaused = true;
}

void GameManager::onResume(EventCustom* pEvent) {
	_bIsPaused = false;
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::onKeyPressed : There is no actor hero");
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;
    events::PauseGameEvent* pPauseGameEvent = nullptr;
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = nullptr;
	events::ChangeTargetEvent* pChangeTargetEvent = nullptr;
	events::ToggleLightEvent* pToggleLightEvent = nullptr;
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pHero->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	game::NodeOwnerComponent* pTargetNodeOwnerComponent, *pSwitchNodeOwnerComponent = nullptr;
	game::NodeOwnerComponent* pLampNodeOwnerComponent = nullptr;
	physics::GeometryComponent* pTargetGeometryComponent = nullptr;
	SwitchableComponent* pLampSwitchableComponent = nullptr;
	core::SynthActor* pOwned, *pSwitch, *pTarget, *pLamp, *pOwnedByHero = nullptr;
	bool bToLamp = false;
	auto dispatcher = EventDispatcher::getInstance();

	_keyPressedCode.push_back(keyCode);

	if (!isPaused()) {
		switch(keyCode) {

			case EventKeyboard::KeyCode::KEY_M:
				CCLOG("Play voice");
				sounds::VoiceManager::getInstance()->playNextVoice();
			break;

			case EventKeyboard::KeyCode::KEY_ESCAPE:
				pPauseGameEvent = new events::PauseGameEvent();
				CCLOG("Dispatching PauseGameEvent");
				dispatcher->dispatchEvent(pPauseGameEvent);
				delete pPauseGameEvent;
			break;

			case EventKeyboard::KeyCode::KEY_Q:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(-1., 0.), true, false, true);
				CCLOG("Dispatching ActorStartMoveEvent LEFT");
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;
            
			case EventKeyboard::KeyCode::KEY_D:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, true);
				CCLOG("Dispatching ActorStartMoveEvent RIGHT");
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;
            
			case EventKeyboard::KeyCode::KEY_SPACE:

				pJumpEvent = new events::JumpEvent(pHero, true);

				CCLOG("Dispatching ActorStartMoveEvent JUMP");
				dispatcher->dispatchEvent(pJumpEvent);
				delete pJumpEvent;
				break;

			case EventKeyboard::KeyCode::KEY_Z:

				//pJumpEvent = new events::JumpEvent(pHero, true);
				CCLOG("Dispatching ActorStartMoveEvent JUMP");
				//dispatcher->dispatchEvent(pJumpEvent);

				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 1.), false, true, true);
				CCLOG("Dispatching ActorStartMoveEvent DOWN");
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;


			case EventKeyboard::KeyCode::KEY_S:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., -1.), false, true, true);
				CCLOG("Dispatching ActorStartMoveEvent DOWN");
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;

			case EventKeyboard::KeyCode::KEY_O:
				pSwitch = getNearLightSwitch(pHero);
				if (pSwitch != nullptr) {

					CCLOG("YOU INTERACTED WITH A LIGHTSWITCH ! EHMAGEHRD !");
					pSwitchNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pSwitch->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
					CCASSERT(pSwitchNodeOwnerComponent != nullptr, "The lightswitch has no node owner component.");
					pLamp = static_cast<core::SynthActor*>(pSwitchNodeOwnerComponent->getOwnedNode());
					CCASSERT(pLamp != nullptr , "The lightswitch has no owned node.");
					CCASSERT(pLamp->getActorType() == core::ActorType::LIGHT, "The lightswitch doesn't own a lamp.");
					pLampSwitchableComponent = static_cast<game::SwitchableComponent*>(pLamp->getComponent(game::SwitchableComponent::COMPONENT_TYPE));
					CCASSERT(pLampSwitchableComponent != nullptr , "The lamp owned by the lightswitch is not switchable.");
				
					if (pLampSwitchableComponent->isOn()) {
						// turn off the light
						pToggleLightEvent = new events::ToggleLightEvent(this, pSwitch, false);
						CCLOG("Dispatching pToggleLightEvent LIGHT OFF");
						dispatcher->dispatchEvent(pToggleLightEvent);
						delete pToggleLightEvent;
					} else {
						// turn on the light
						pToggleLightEvent = new events::ToggleLightEvent(this, pSwitch, true);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
						dispatcher->dispatchEvent(pToggleLightEvent);
						delete pToggleLightEvent;
					}

				}

				break;

			case EventKeyboard::KeyCode::KEY_P:
				// if the hero owns an actor
				if (pNodeOwnerComponent->getOwnedNode() != nullptr) {
					pOwnedByHero = static_cast<core::SynthActor*>(pNodeOwnerComponent->getOwnedNode());
					pTarget = getNearActor(pHero);
					// the owned actor can go to a lamp or exchange with a firefly
					if (pTarget != nullptr) {
						if (pTarget->isFirefly()) {
							pTargetGeometryComponent = static_cast<physics::GeometryComponent*>(pTarget->getComponent(physics::GeometryComponent::COMPONENT_TYPE));

							// if the firefly is owned by a lamp
							for (auto maybeALamp : _levelActors) {
								if(!bToLamp) {
									// if the actor is a lamp
									if (maybeALamp->getActorType() == core::ActorType::LIGHT) {
										pLampNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(maybeALamp->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
										// if the lamp owns the firefly
										if (pLampNodeOwnerComponent != nullptr && pLampNodeOwnerComponent->getOwnedNode() != nullptr && static_cast<core::SynthActor*>(pLampNodeOwnerComponent->getOwnedNode())->getActorID() == pTarget->getActorID()) {
										
											// the firefly of the lamp goes to the hero
											pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
											CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
											dispatcher->dispatchEvent(pChangeTargetEvent); 
											delete pChangeTargetEvent;
											// the firefly of the lamp is now owned by the hero
											pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pTarget, pHero, maybeALamp);
											CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE WITH NEW FIREFLY");
											dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
											delete pChangeNodeOwnerEvent;

											// the owned firefly goes to the lamp
											pChangeTargetEvent = new events::ChangeTargetEvent(pOwnedByHero, maybeALamp);
											CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
											dispatcher->dispatchEvent(pChangeTargetEvent);
											delete pChangeTargetEvent;
											// the owned firefly is now owned by the lamp
											pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pOwnedByHero, maybeALamp, pHero);
											CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
											dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
											delete pChangeNodeOwnerEvent;

											bToLamp = true;
										}
									}
								}
							}

							if(!bToLamp) {
								// the firefly goes to the hero
								pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
								CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
								dispatcher->dispatchEvent(pChangeTargetEvent); 
								delete pChangeTargetEvent;
								// the firefly is now owned by the hero
								pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pTarget, pHero, nullptr);
								CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE WITH NEW FIREFLY");
								dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
								delete pChangeNodeOwnerEvent;

								// the firefly goes to the targetted firefly position
								pChangeTargetEvent = new events::ChangeTargetEvent(pOwnedByHero, pTargetGeometryComponent->getPosition());
								CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
								dispatcher->dispatchEvent(pChangeTargetEvent); 
								delete pChangeTargetEvent;
								// the firefly previously owned is now free
								pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pOwnedByHero, nullptr, pHero);
								CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : the owned node is free");
								dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
								delete pChangeNodeOwnerEvent;
							}

						} else if (pTarget->getActorType() == core::ActorType::LIGHT) {
							pTargetNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pTarget->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
							CCASSERT(pTargetNodeOwnerComponent != nullptr, "The target lamp need a nodeownercomponent");
							pOwned = static_cast<core::SynthActor*>(pTargetNodeOwnerComponent->getOwnedNode());

							// if the light owns a firefly
							if(pOwned != nullptr && pOwned->isFirefly()) {
								// the lamp firefly goes to the hero
								pChangeTargetEvent = new events::ChangeTargetEvent(pOwned, pHero);
								CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
								dispatcher->dispatchEvent(pChangeTargetEvent);
								delete pChangeTargetEvent;
							}

							// the owned firefly goes to the lamp
							pChangeTargetEvent = new events::ChangeTargetEvent(pOwnedByHero, pTarget);
							CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
							dispatcher->dispatchEvent(pChangeTargetEvent);
							delete pChangeTargetEvent;

							// if the light owns a firefly
							if(pOwned != nullptr && pOwned->isFirefly()) {
								// the lamp firefly is now owned by the hero
								pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pOwned, pHero, pTarget);
								CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
								dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
								delete pChangeNodeOwnerEvent;
							}

							// the owned firefly is now owned by the lamp
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pOwnedByHero, pTarget, pHero);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
							delete pChangeNodeOwnerEvent;
						
						}
					}
				
				// if the hero has no actor
				} else {
					pTarget = getNearActor(pHero);
					if(pTarget != nullptr) {
						// if the target is a light
						if (pTarget->getActorType() == core::ActorType::LIGHT) {
							pTargetNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pTarget->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
							CCASSERT(pTargetNodeOwnerComponent != nullptr, "The target lamp need a nodeownercomponent");
							pOwned = static_cast<core::SynthActor*>(pTargetNodeOwnerComponent->getOwnedNode());

							// if the light owns a firefly
							if(pOwned != nullptr && pOwned->isFirefly()) {
								// the firefly owned by the light is now owned by the hero
								pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pOwned, pHero, pTarget);
								CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
								dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
								delete pChangeNodeOwnerEvent;
								// the firefly owned by the light goes to the hero
								pChangeTargetEvent = new events::ChangeTargetEvent(pOwned, pHero);
								CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
								dispatcher->dispatchEvent(pChangeTargetEvent);
								delete pChangeTargetEvent;
							}
						// if the target is a firefly
						} else if (pTarget->isFirefly()) {
							// if the firefly is owned by a lamp
							for (auto maybeALamp : _levelActors) {
								if(!bToLamp) {
									// if the actor is a lamp
									if (maybeALamp->getActorType() == core::ActorType::LIGHT) {
										pLampNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(maybeALamp->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
										// if the lamp owns the firefly
										if (pLampNodeOwnerComponent != nullptr && pLampNodeOwnerComponent->getOwnedNode() != nullptr && static_cast<core::SynthActor*>(pLampNodeOwnerComponent->getOwnedNode())->getActorID() == pTarget->getActorID()) {
									
											// the firefly goes to the hero
											pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
											CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
											dispatcher->dispatchEvent(pChangeTargetEvent);
											delete pChangeTargetEvent;
											// the firefly is owned by the hero
											pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pTarget, pHero, maybeALamp);
											CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
											dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
											delete pChangeNodeOwnerEvent;

											bToLamp = true;
										}
									}
								}
							}
						} else {
							// the target is owned by the hero
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(this, pTarget, pHero, nullptr);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
							delete pChangeNodeOwnerEvent;
							// the target goes to the hero
							pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
							CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
							dispatcher->dispatchEvent(pChangeTargetEvent);
							delete pChangeTargetEvent;
						}

					}
				}

			break;

			default:
				break;
		}
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::onKeyReleased : There is no actor hero");
    events::EditMoveEvent* pEditMoveEvent;
    events::JumpEvent* pJumpEvent = nullptr;
    
    auto dispatcher = EventDispatcher::getInstance();

	if (!isPaused()) {
		switch(keyCode) {
			case EventKeyboard::KeyCode::KEY_Q:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;

			case EventKeyboard::KeyCode::KEY_D:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;

			case EventKeyboard::KeyCode::KEY_Z:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 0.), false, true, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;

			case EventKeyboard::KeyCode::KEY_S:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 0.), false, true, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				delete pEditMoveEvent;
				break;

			case EventKeyboard::KeyCode::KEY_SPACE:
				pJumpEvent = new events::JumpEvent(pHero, false);
				dispatcher->dispatchEvent(pJumpEvent);
				delete pJumpEvent;
				break;

			default:
				break;
		}
		_keyPressedCode.erase(std::remove(_keyPressedCode.begin(), _keyPressedCode.end(), keyCode), _keyPressedCode.end());

		for(std::vector<EventKeyboard::KeyCode>::iterator it = _keyPressedCode.begin(); it != _keyPressedCode.end(); ++it) {
			switch(*it) {
				case EventKeyboard::KeyCode::KEY_Q:
					pEditMoveEvent = new events::EditMoveEvent(pHero, Point(-1., 0.), true, false, true);
					dispatcher->dispatchEvent(pEditMoveEvent);
					delete pEditMoveEvent;
					break;
            
				case EventKeyboard::KeyCode::KEY_D:
					pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, true);
					dispatcher->dispatchEvent(pEditMoveEvent);
					delete pEditMoveEvent;
					break;

				case EventKeyboard::KeyCode::KEY_Z:
					pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., 1.), false, true, true);
					dispatcher->dispatchEvent(pEditMoveEvent);
					delete pEditMoveEvent;
					break;
            
				case EventKeyboard::KeyCode::KEY_S:
					pEditMoveEvent = new events::EditMoveEvent(pHero, Point(0., -1.), false, true, true);
					dispatcher->dispatchEvent(pEditMoveEvent);
					delete pEditMoveEvent;
					break;

			}

		}
	}

}

Color4B GameManager::getLightColor(core::SynthActor* pLight) {
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorsByType(core::ActorType type) {
	std::vector<core::SynthActor*> actorsRet;

	for (auto actor : _levelActors) {
		if(actor->getActorType() == type) {
			actorsRet.push_back(actor);
		}
	}
	return actorsRet;
}

core::SynthActor* GameManager::getNearActor(core::SynthActor* actor) {
	core::SynthActor* pRes = nullptr;
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(actor->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(actor->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	physics::GeometryComponent* pCandidateGeometryComponent = nullptr;
	Point actorPosition = pGeometryComponent->getPosition();
	Point candidatePosition = Point::ZERO;
	float distance = 0;
	for (auto candidate : _levelActors) {
		if (actor != candidate && pNodeOwnerComponent->getOwnedNode() != candidate) {
			// if the actor owns an other actor and if candidate is a light or a firefly
			if ( (pNodeOwnerComponent->getOwnedNode() != nullptr && (candidate->getActorType() == core::ActorType::LIGHT || candidate->isFirefly() )) ) {
				pCandidateGeometryComponent = static_cast<physics::GeometryComponent*>(candidate->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
				candidatePosition = pCandidateGeometryComponent->getPosition();
				if ( pCandidateGeometryComponent != nullptr ) {
					distance = sqrt( (candidatePosition.x - actorPosition.x)*(candidatePosition.x - actorPosition.x) + (candidatePosition.y - actorPosition.y)*(candidatePosition.y - actorPosition.y) );
					if (distance < pGeometryComponent->getSize().height ) {
						CCLOG("NEAR ACTOR FOUND");
						pRes = candidate;
						return pRes;
					}
				}
			// or if the actor has no owned node and the candidate is a firefly
			}
			if ( pNodeOwnerComponent->getOwnedNode() == nullptr && (candidate->getTag() == core::ActorType::BLUE_FIREFLY || candidate->isFirefly() ) ) {
				pCandidateGeometryComponent = static_cast<physics::GeometryComponent*>(candidate->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
				candidatePosition = pCandidateGeometryComponent->getPosition();
				if ( pCandidateGeometryComponent != nullptr ) {
					distance = sqrt( (candidatePosition.x - actorPosition.x)*(candidatePosition.x - actorPosition.x) + (candidatePosition.y - actorPosition.y)*(candidatePosition.y - actorPosition.y) );
					if (distance < pGeometryComponent->getSize().height ) {
						CCLOG("NEAR ACTOR FOUND");
						pRes = candidate;
						return pRes;
					}
				}
			}
		}
	}
	return pRes;
}

core::SynthActor* GameManager::getNearLightSwitch(core::SynthActor* actor) {
	core::SynthActor* pRes = nullptr;
	physics::GeometryComponent* pGeometryComponent = static_cast<physics::GeometryComponent*>(actor->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	physics::GeometryComponent* pCandidateGeometryComponent = nullptr;
	Point actorPosition = pGeometryComponent->getPosition();
	Point candidatePosition = Point::ZERO;
	float distance = 0;
	for (auto candidate : _levelActors) {
		// if candidate is a lightswitch
		if (candidate->getActorType() == core::ActorType::LIGHTSWITCH) {
			pCandidateGeometryComponent = static_cast<physics::GeometryComponent*>(candidate->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
			candidatePosition = pCandidateGeometryComponent->getPosition();
			if ( pCandidateGeometryComponent != nullptr ) {
				distance = sqrt( (candidatePosition.x - actorPosition.x)*(candidatePosition.x - actorPosition.x) + (candidatePosition.y - actorPosition.y)*(candidatePosition.y - actorPosition.y) );
				if (distance < pGeometryComponent->getSize().height ) {
					CCLOG("NEAR ACTOR FOUND");
					pRes = candidate;
					return pRes;
				}
			}
		}
	}
	return pRes;
}

}  // namespace game
