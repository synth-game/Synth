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
	_pParallaxManager->addChild(_pBackgroundLayer, 1, Point(0.7f, 0.7f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pIntermediarLayer, 2, Point(0.8f, 0.8f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pLevelLayer, 3, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSkinningLayer, 4, Point(1.f, 1.f), Point(0.f, 0.f));
	_pParallaxManager->addChild(_pSubtitlesLayer, 5, Point(1.f, 1.f), Point(0.f, 0.f));
	Layer::addChild(_pParallaxManager);

	//TEST ZONE - BEGIN
	Sprite* pBgSprite = Sprite::create("sprites/decor.jpg");
	pBgSprite->setAnchorPoint(Point::ZERO);
	_pBackgroundLayer->addChild(pBgSprite);

	_levelActors = game::LevelFactory::getInstance()->buildActors("test", _pLevelLayer);
	_triggers = game::LevelFactory::getInstance()->buildTriggers("test");

	hero = GameManager::getActorsByTag("HERO").at(0);

	LevelSprite* pLevelSprite = LevelSprite::create("levels/test/bitmask.png", hero);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_0.png")->getTexture(), Point(390.f, 260.f), Color4B::RED);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_1.png")->getTexture(), Point(100.f, 580.f), Color4B::BLUE);
	pLevelSprite->addLight(Sprite::create("levels/test/PREC_light_2.png")->getTexture(), Point(590.f, 260.f), Color4B::GREEN);
	_pLevelLayer->addChild(pLevelSprite, 0);
	//TEST ZONE - END

	return bTest;
}

void GameManager::update(float fDt) {
	for (auto actor : _levelActors) {
		actor->update(fDt);
	}
	Point heroPos = static_cast<physics::GeometryComponent*>(hero->getComponent(physics::GeometryComponent::COMPONENT_TYPE))->getPosition();
	if(_triggers["WIN"].containsPoint(heroPos)) {
		CCLOG("YOU WIN");
		events::WinEvent* pWinEvent = new events::WinEvent();
	}
}

void GameManager::loadLevel(int iLevelId) {

}

void GameManager::resetLevel() {
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
	events::EditMoveEvent* pEditMoveEvent = nullptr;
    events::JumpEvent* pJumpEvent = nullptr;
	events::ChangeNodeOwnerEvent* pChangeNodeOwnerEvent = nullptr;
	events::ChangeTargetEvent* pChangeTargetEvent = nullptr;
	game::NodeOwnerComponent* pNodeOwnerComponent = static_cast<game::NodeOwnerComponent*>(hero->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
	physics::GeometryComponent* pTargetGeometryComponent = nullptr;

	core::SynthActor* pTarget = nullptr;

	auto dispatcher = EventDispatcher::getInstance();
	_keyPressedCode.push(keyCode);

    switch(_keyPressedCode.top()) {
        case EventKeyboard::KeyCode::KEY_Q:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(-1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent LEFT");
            dispatcher->dispatchEvent(pEditMoveEvent);
            break;
            
        case EventKeyboard::KeyCode::KEY_D:
            pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, true);
            CCLOG("Dispatching ActorStartMoveEvent RIGHT");
            dispatcher->dispatchEvent(pEditMoveEvent);
            break;
            
        case EventKeyboard::KeyCode::KEY_SPACE:
            pJumpEvent = new events::JumpEvent(hero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_Z:
            pJumpEvent = new events::JumpEvent(hero, true);
            CCLOG("Dispatching ActorStartMoveEvent JUMP");
            dispatcher->dispatchEvent(pJumpEvent);
            break;

		case EventKeyboard::KeyCode::KEY_P:
			// if the hero owns an actor
			if (pNodeOwnerComponent->getOwnedNode() != nullptr) {
				pTarget = getNearActor(hero);
				// the owned actor can go to a lamp or exchange with a firefly
				if (pTarget != nullptr) {
					if (pTarget->isFirefly()) {
						pTargetGeometryComponent = static_cast<physics::GeometryComponent*>(pTarget->getComponent(physics::GeometryComponent::COMPONENT_TYPE));
						pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTargetGeometryComponent->getPosition());
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
						dispatcher->dispatchEvent(pChangeTargetEvent); 

						pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, hero);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (FIREFLY)");
						dispatcher->dispatchEvent(pChangeTargetEvent); 

						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), nullptr);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : the owned node is free");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pTarget, hero);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE WITH NEW FIREFLY");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);

					} else if (pTarget->getActorType() == core::ActorType::LIGHT) {
						pChangeTargetEvent = new events::ChangeTargetEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET OTHER ACTOR (LAMP)");
						dispatcher->dispatchEvent(pChangeTargetEvent);

						pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pNodeOwnerComponent->getOwnedNode(), pTarget);
						CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE : owned node belongs to lamp");
						dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
					}
				}
				
			// if the hero has no actor
			} else {
				pTarget = getNearActor(hero);
				if(pTarget != nullptr) {
					pChangeNodeOwnerEvent = new events::ChangeNodeOwnerEvent(pTarget, hero);
					CCLOG("Dispatching ChangeNodeOwnerEvent CHANGE NODE");
					dispatcher->dispatchEvent(pChangeNodeOwnerEvent);
					pChangeTargetEvent = new events::ChangeTargetEvent(pTarget, hero);
					CCLOG("Dispatching pChangeTargetEvent CHANGE TARGET");
					dispatcher->dispatchEvent(pChangeTargetEvent);
				}
			}

		break;

		default:
			break;
	}
}

void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    events::EditMoveEvent* pEditMoveEvent;
    auto dispatcher = EventDispatcher::getInstance();

	if(keyCode == _keyPressedCode.top()) {
		switch(keyCode) {
			case EventKeyboard::KeyCode::KEY_Q:
				pEditMoveEvent = new events::EditMoveEvent(hero, Point(1., 0.), true, false, false);
				dispatcher->dispatchEvent(pEditMoveEvent);
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
		_keyPressedCode.pop();
	}
}

Color4B GameManager::getLightColor(core::SynthActor* pLight) {
	return Color4B::BLACK;
}

std::vector<core::SynthActor*> GameManager::getActorsByTag(std::string sTag) {
	std::vector<core::SynthActor*> emptyVec;

	std::map<std::string, core::ActorType> actorTagsMap;
	// invert enum actor type
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("HERO",				core::ActorType::HERO));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("BLUE_FIREFLY",		core::ActorType::BLUE_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("RED_FIREFLY",		core::ActorType::RED_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("GREEN_FIREFLY",	core::ActorType::GREEN_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHT",			core::ActorType::LIGHT));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHTSWITCH",		core::ActorType::LIGHTSWITCH));

	for (auto actor : _levelActors) {
		if(actor->getActorType() == actorTagsMap[sTag]) {
			emptyVec.push_back(actor);
		}
	}
	return emptyVec;
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

//void GameManager::onEditMove(EventCustom* pEvent) { 
//	CCLOG("on edit move gm");
//}

}  // namespace game
