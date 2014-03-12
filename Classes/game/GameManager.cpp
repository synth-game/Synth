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
#include "LevelSprite.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/CollisionComponent.h"
#include "physics/PhysicCollision.h"
#include "physics/FollowMovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "graphics/FireflyAnimatedSpriteComponent.h"
#include "game/NodeOwnerComponent.h"

#include "events/EditMoveEvent.h"
#include "events/JumpEvent.h"
#include "events/ChangeNodeOwnerEvent.h"
#include "events/ChangeTargetEvent.h"
#include "Events/WinEvent.h"

#include <SimpleAudioEngine.h>

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

	//TEST ZONE - BEGIN

	loadLevel("01");

	//TEST ZONE - END

	return bTest;
}

void GameManager::update(float fDt) {
	core::SynthActor* pHero = nullptr;
	pHero = getActorsByType(core::ActorType::HERO)[0];
	CCASSERT(pHero != nullptr, "GameManager:update() There is no actor hero");
	physics::GeometryComponent* pGeometryComp = dynamic_cast<physics::GeometryComponent*>(pHero->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
	CCASSERT(pGeometryComp != nullptr, "Hero actor need a GeometryComponent");
	if(_triggers["WIN"].containsPoint(pGeometryComp->getPosition())) {
		CCLOG("YOU WIN");
		events::WinEvent* pWinEvent = new events::WinEvent();
		GameManager::resetLevel();
	}

	for (auto actor : _levelActors) {
		actor->update(fDt);
	}
}

void GameManager::loadLevel(/*int iLevelId*/std::string level) {

	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	pBgSprite->setAnchorPoint(Point::ZERO);
	pBgSprite->setScale(2.f);
	_pBackgroundLayer->addChild(pBgSprite);

	_levelActors = game::LevelFactory::getInstance()->buildActors(level, _pLevelLayer);
	_triggers = game::LevelFactory::getInstance()->buildTriggers(level);

	LevelSprite* pLevelSprite = LevelSprite::create(std::string("levels/"+level+"/bitmask.png").c_str(), getActorsByType(core::ActorType::HERO)[0]);
	pLevelSprite->addLight(Sprite::create(std::string("levels/"+level+"/PREC_light_0.png").c_str())->getTexture(), Point(490.f, 260.f), Color4B::RED);
	pLevelSprite->addLight(Sprite::create(std::string("levels/"+level+"/PREC_light_1.png").c_str())->getTexture(), Point(590.f, 260.f), Color4B::BLUE);
	_pLevelLayer->addChild(pLevelSprite, 0, 42);
}

void GameManager::clearLevel() {
	for(auto obj : _levelActors) {
		delete obj;
		obj = nullptr;
	}
	_levelActors.clear();
	_triggers.clear();

	_pBackgroundLayer->removeAllChildren();
	_pIntermediarLayer->removeAllChildren();
	_pLevelLayer->removeAllChildren();
	_pSkinningLayer->removeAllChildren();
	_pSubtitlesLayer->removeAllChildren();
}

void GameManager::resetLevel() {
	clearLevel();
	//loadLevel("test");
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	core::SynthActor* pHero = getActorsByType(core::ActorType::HERO)[0];
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = nullptr;
	events::ChangeTargetEvent* pChangeTargetEvent = nullptr;
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(pHero->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	game::NodeOwnerComponent* pTargetNodeOwnerComponent = nullptr;
	physics::GeometryComponent* pTargetGeometryComponent = nullptr;
	core::SynthActor* pOwned = nullptr;

	core::SynthActor* pTarget = nullptr;

	auto dispatcher = EventDispatcher::getInstance();
	_keyPressedCode.push(keyCode);

    switch(_keyPressedCode.top()) {
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
						pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTargetGeometryComponent->getPosition());
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
						dispatcher->dispatchEvent(pChangeTargetEvent); 

						pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, pHero);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
						dispatcher->dispatchEvent(pChangeTargetEvent); 

						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), nullptr);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : the owned node is free");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

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

							// the lamp firefly is now owned by the hero
							pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pOwned, pHero);
							CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
							dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
						}
						// the owned firefly goes to the lamp
						pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
						dispatcher->dispatchEvent(pChangeTargetEvent);

						// the owned firefly is now owned by the lamp
						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
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
					// if the target is not a light
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
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();

	if(keyCode == _keyPressedCode.top()) {
		switch(keyCode) {
			case EventKeyboard::KeyCode::KEY_Q:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(1., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
				break;
			case EventKeyboard::KeyCode::KEY_D:
				pEditMoveEvent = new events::EditMoveEvent(pHero, Point(-1., 0.), true, false, false);
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
		_keyPressedCode.pop();
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
