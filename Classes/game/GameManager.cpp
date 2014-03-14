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
#include "core/ActorType.h"
#include "core/SynthConfig.h"
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "physics/FollowMovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "graphics/FireflyAnimatedSpriteComponent.h"
#include "graphics/GraphicManager.h"
#include "game/NodeOwnerComponent.h"
#include "system/IOManager.h"
#include "sounds/SoundType.h"

#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeTargetEvent.h"
#include "events/WinEvent.h"
#include "events/DeathEvent.h"
#include "events/ResetLevelEvent.h"
#include "events/EnterLightEvent.h"

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
	, _pParallaxManager(nullptr)
	, _keyPressedCode() {

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
	win = false;
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
	EventDispatcher::getInstance()->addEventListenerWithFixedPriority(_pEnterLightListener, 1);

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

	// NE PAS DECOMMENTER SVP , INIT MUSIC FAIT DANS LE SOUND MANAGER FmodAudioPlayer::sharedPlayer()->InitMusic(); NE PAS DECOMMENTER SVP
	//FmodAudioPlayer::sharedPlayer()->PlayMusicTrack(FmodAudioPlayer::tracks::BLUE);
	//TEST ZONE - END

	return bTest;

	// Init sounds ids
	stepsSoundId = -1; //-1 >> not playing
}

void GameManager::update(float fDt) {
	core::SynthActor* pHero = nullptr;
	pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::update : There is no actor hero");
	physics::GeometryComponent* pGeometryComp = dynamic_cast<physics::GeometryComponent*>(pHero->getComponent(physics::GeometryComponent::COMPONENT_TYPE));

	CCASSERT(pGeometryComp != nullptr, "Hero actor need a GeometryComponent");
	if(_triggers["WIN"].containsPoint(pGeometryComp->getPosition()) && !win) {
		CCLOG("GameManager::update : YOU WIN");
		events::WinEvent* pWinEvent = new events::WinEvent();
		EventDispatcher::getInstance()->dispatchEvent(pWinEvent);
	}

	for (auto actor : _levelActors) {
		actor->update(fDt);
	}

	FmodAudioPlayer::sharedPlayer()->Update(fDt);
}

void GameManager::loadLevel(/*int iLevelId*/std::string level) {
    CCLOG("GameManager::loadLevel : LOAD LEVEL");
	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	pBgSprite->setAnchorPoint(Point::ZERO);
	pBgSprite->setScale(2.f);
	_pBackgroundLayer->addChild(pBgSprite);

	// Build actors and light collisions
	_levelActors = game::LevelFactory::getInstance()->buildActors(level, _pLevelLayer);
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	physics::CollisionComponent* pCollisionComp = dynamic_cast<physics::CollisionComponent*>(pHero->getComponent(physics::CollisionComponent::COMPONENT_TYPE));
	pCollisionComp->addLightCollision(game::LevelFactory::getInstance()->buildLightsCollision(level, getActorsByType(core::ActorType::LIGHT)));
	
	// Build triggers
	_triggers = game::LevelFactory::getInstance()->buildTriggers(level);

	// Display debug rectangle for triggers
	for (std::map<std::string, Rect>::iterator it = _triggers.begin(); it != _triggers.end(); ++it) {
		Sprite* rect = Sprite::create("levels/test/rect.png");
		rect->setPosition(it->second.origin);
		rect->setAnchorPoint(Point(0,0));
		rect->setScaleX(it->second.size.width/rect->getContentSize().width);
		rect->setScaleY(it->second.size.height/rect->getContentSize().height);
		_pLevelLayer->addChild(rect, 50);
	}

	// Build level Sprite
	_pLevelSprite = game::LevelFactory::getInstance()->buildLevelSprite(level, _pLevelLayer, getActorsByType(core::ActorType::LIGHT));

	win = false;

}

void GameManager::clearLevel() {
	CCLOG("GameManager::clearLevel : CLEAR LEVEL");
	for(auto obj : _levelActors) {
		obj->removeAllComponents();
		obj->removeFromParent();
	}

	_levelActors.clear();
	_triggers.clear();

	_pBackgroundLayer->removeAllChildren();
	_pIntermediarLayer->removeAllChildren();
	_pLevelLayer->removeAllChildren();

	_pLevelSprite = nullptr;

	_pSkinningLayer->removeAllChildren();
	_pSubtitlesLayer->removeAllChildren();

	graphics::GraphicManager::getInstance()->reset();

}

void GameManager::resetLevel() {
	if(!win) {
		CCLOG("GameManager::resetLevel : Clear and reload level");
		win = true;
		clearLevel();
		loadLevel(_levelsName[_iCurrentLevelId]);
	}
}

void GameManager::nextLevel() {
	if(!win) {
		CCLOG("GameManager::nextLevel : Clear and load next level");
		win = true;
		clearLevel();
		//loadLevel(_levelsName[++_iCurrentLevelId]);
		loadLevel("01");
	}
}

void GameManager::onEnterLight(EventCustom* pEvent) {
	CCLOG("GameManager::onEnterLight : You just entered a light");
	events::EnterLightEvent* enterLightEvent = static_cast<events::EnterLightEvent*>(pEvent);

	Color4B lightColor = enterLightEvent->getLightingColor();

	if (lightColor == Color4B::RED) {
		CCLOG("GameManager::onEnterLight : You die !");
		events::DeathEvent* pDeathEvent = new events::DeathEvent();
		EventDispatcher::getInstance()->dispatchEvent(pDeathEvent);
	}
}

void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::onKeyPressed : There is no actor hero");
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = nullptr;
	events::ChangeTargetEvent* pChangeTargetEvent = nullptr;
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pHero->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	game::NodeOwnerComponent* pTargetNodeOwnerComponent = nullptr;
	game::NodeOwnerComponent* pLampNodeOwnerComponent = nullptr;
	physics::GeometryComponent* pTargetGeometryComponent = nullptr;
	core::SynthActor* pOwned = nullptr;

	core::SynthActor* pTarget = nullptr;

	bool bToLamp = false;

	auto dispatcher = EventDispatcher::getInstance();

	_keyPressedCode.push_back(keyCode);


	switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_Q:
            pEditMoveEvent = new events::EditMoveEvent(pHero, Point(-1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent LEFT");
            dispatcher->dispatchEvent(pEditMoveEvent);
			break;
            
        case EventKeyboard::KeyCode::KEY_D:
            pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent RIGHT");
            dispatcher->dispatchEvent(pEditMoveEvent);
			break;
            
        case EventKeyboard::KeyCode::KEY_SPACE:

            pJumpEvent = new events::JumpEvent(pHero, true);

            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_Z:
            pJumpEvent = new events::JumpEvent(pHero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_P:
			// if the hero owns an actor
			if (pNodeOwnerComponent->getOwnedNode() != nullptr) {
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
									
										// the owned firefly goes to the lamp
										pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), maybeALamp);
										CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
										dispatcher->dispatchEvent(pChangeTargetEvent);
										// the owned firefly is now owned by the lamp
										pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), maybeALamp);
										CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
										dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

										bToLamp = true;
									}
								}
							}
						}

						if(!bToLamp) {
							// the firefly goes to the targetted firefly position
							pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTargetGeometryComponent->getPosition());
							CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
							dispatcher->dispatchEvent(pChangeTargetEvent); 
							// the firefly previously owned is now free
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), nullptr);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : the owned node is free");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
						}

						// the firefly goes to the hero
						pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
						dispatcher->dispatchEvent(pChangeTargetEvent); 
						// the firefly is now owned by the hero
						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pTarget, pHero);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE WITH NEW FIREFLY");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

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
						}

						// the owned firefly goes to the lamp
						pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
						dispatcher->dispatchEvent(pChangeTargetEvent);

						// the owned firefly is now owned by the lamp
						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

						// if the light owns a firefly
						if(pOwned != nullptr && pOwned->isFirefly()) {
							// the lamp firefly is now owned by the hero
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pOwned, pHero);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
						}

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
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pOwned, pHero);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
							// the firefly owned by the light goes to the hero
							pChangeTargetEvent = new events::ChangeTargetEvent(pOwned, pHero);
							CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
							dispatcher->dispatchEvent(pChangeTargetEvent);
						}
					} else {
						// the target is owned by the hero
						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pTarget, pHero);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
						// the target goes to the hero
						pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
						dispatcher->dispatchEvent(pChangeTargetEvent);
					}

				}
			}

		break;

		default:
			break;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager::onKeyReleased : There is no actor hero");
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();

	switch(keyCode) {
		case EventKeyboard::KeyCode::KEY_Q:
			pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, false);
			dispatcher->dispatchEvent(pEditMoveEvent);

			//FmodAudioPlayer::sharedPlayer()->stopEffect(stepsSoundId);
			stepsSoundId = -1;

			break;
		case EventKeyboard::KeyCode::KEY_D:
			pEditMoveEvent = new events::EditMoveEvent(pHero, Point(-1., 0.), true, false, false);
			dispatcher->dispatchEvent(pEditMoveEvent);

			//FmodAudioPlayer::sharedPlayer()->stopEffect(stepsSoundId);
			stepsSoundId = -1;

			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			/*jumpEvent = new ActorJumpEvent(_hero);
			jumpEvent->_bStart = false;
			dispatcher->dispatchEvent(jumpEvent);*/

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
				break;
            
			case EventKeyboard::KeyCode::KEY_D:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, true);
				dispatcher->dispatchEvent(pEditMoveEvent);
				break;
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
					}
				}
			}
		}
	}
	return pRes;
}

}  // namespace game
