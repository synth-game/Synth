/*!
 * \file LevelFactory.cpp
 * \brief Singleton dealing with the creation of actors, light maps, level sprites, triggers
 * \author Xopi
 * \date 26/02/2014
 */
#include "LevelFactory.h"
#include "game/NodeOwnerComponent.h"
#include "game/LightAttrComponent.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/FollowMovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "graphics/FireFlyAnimatedSpriteComponent.h"
#include "system/IOManager.h"
#include "sounds/HeroSoundComponent.h"
#include "sounds/FireflySoundComponent.h"

namespace game {

LevelFactory* LevelFactory::_pInstance = nullptr;

LevelFactory::LevelFactory() {
}

LevelFactory::~LevelFactory() {
}

LevelFactory* LevelFactory::getInstance() {
	if(_pInstance == nullptr) {
        _pInstance = new LevelFactory();
    }
	return _pInstance;
}

std::vector<core::SynthActor*> LevelFactory::buildActors(std::string levelName, Layer* pLevelLayer) {

	std::vector<core::SynthActor*> aActors;
	std::map<std::string, core::ActorType> actorTagsMap;
	std::map<std::string, core::ComponentType> componentTagsMap;

	// invert enum actor type
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("HERO",				core::ActorType::HERO));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("BLUE_FIREFLY",		core::ActorType::BLUE_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("RED_FIREFLY",		core::ActorType::RED_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("GREEN_FIREFLY",	core::ActorType::GREEN_FIREFLY));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHT",			core::ActorType::LIGHT));
	actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHTSWITCH",		core::ActorType::LIGHTSWITCH));

	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("GEOMETRY",					core::ComponentType::GEOMETRY));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("MOVEMENT",					core::ComponentType::MOVEMENT));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("FOLLOWMOVEMENT",			core::ComponentType::FOLLOWMOVEMENT));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("COLLISION",				core::ComponentType::COLLISION));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("SPRITE",					core::ComponentType::SPRITE));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("HEROANIMATEDSPRITE",		core::ComponentType::HEROANIMATEDSPRITE));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("FIREFLYANIMATEDSPRITE",	core::ComponentType::FIREFLYANIMATEDSPRITE));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("FOLLOWMOVEMENT",			core::ComponentType::FOLLOWMOVEMENT));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("NODEOWNER",				core::ComponentType::NODEOWNER));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("LIGHTATTR",				core::ComponentType::LIGHTATTR));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("HEROSOUND",				core::ComponentType::HEROSOUND));
	componentTagsMap.insert(std::pair<std::string, core::ComponentType>("FIREFLYSOUND",				core::ComponentType::FIREFLYSOUND));

	// parsing actors
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	synthsystem::IOManager* ioManager = synthsystem::IOManager::getInstance();
	pXMLFile = ioManager->loadXML("levels/"+levelName+"/actors.xml");
	if(pXMLFile != nullptr) {
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pActorData, *pComponentData, *pPositionData, *pSizeData, *pRotateData, *pAnchorPointData, *pAccelerationData, *pGravityData ,*pOwnerData;
		std::string actorType, componentType, name, ownedIdText;
		float positionX, positionY, anchorPointX, anchorPointY, rotate, accelerationX, accelerationY, gravityX, gravityY, width, height = 0;
		int ownerId;
		std::vector<int> aOwnerIds;
		pActorData = pXMLFile->FirstChildElement("actor");
		while (pActorData) {

			// Create actor
			actorType = pActorData->Attribute("type");
			core::SynthActor* actor = new core::SynthActor(actorTagsMap[actorType]);
			aActors.push_back(actor);

			// Create components
			std::vector<core::SynthComponent*> aComponents;
			pComponentData = pActorData->FirstChildElement("component");

			ownerId = -1;

			while(pComponentData) {
				componentType = pComponentData->Attribute("type");
				switch(componentTagsMap[componentType]) {
				case core::ComponentType::GEOMETRY:
					// Position
					pPositionData = pComponentData->FirstChildElement("position");
					positionX = pPositionData->FloatAttribute("x");
					positionY = pPositionData->FloatAttribute("y");
					// Size
					pSizeData = pComponentData->FirstChildElement("size");
					width = pSizeData->FloatAttribute("width");
					height = pSizeData->FloatAttribute("height");
					// Rotate
					pRotateData = pComponentData->FirstChildElement("rotate");
					rotate = atof(pRotateData->GetText());
					// Anchor point
					pAnchorPointData = pComponentData->FirstChildElement("anchorPoint");
					anchorPointX = pAnchorPointData->FloatAttribute("x");
					anchorPointY = pAnchorPointData->FloatAttribute("y");
					// Create GeometryComponent
					aComponents.push_back(physics::GeometryComponent::create(Point(positionX, positionY), Size(width, height), rotate, Point(anchorPointX, anchorPointY)));
					break;
				case core::ComponentType::MOVEMENT:
					// Acceleration
					pAccelerationData = pComponentData->FirstChildElement("acceleration");
					accelerationX = pAccelerationData->FloatAttribute("x");
					accelerationY = pAccelerationData->FloatAttribute("y");
					// Gravity
					pGravityData = pComponentData->FirstChildElement("gravity");
					gravityX = pGravityData->FloatAttribute("x");
					gravityY = pGravityData->FloatAttribute("y");
					// Create MovementComponent
					aComponents.push_back(physics::MovementComponent::create(Point(accelerationX, accelerationY), Point(gravityX, gravityY), 0.5f, 3.0f));
					break;
				case core::ComponentType::FOLLOWMOVEMENT:
					// Acceleration
					pAccelerationData = pComponentData->FirstChildElement("acceleration");
					accelerationX = pAccelerationData->FloatAttribute("x");
					accelerationY = pAccelerationData->FloatAttribute("y");
					// Create FollowMovementComponent
					aComponents.push_back(physics::FollowMovementComponent::create(Point(accelerationX, accelerationY), actor));
					break;
				case core::ComponentType::COLLISION:
					// Create CollisionComponent
					aComponents.push_back(__createCollisionComponent(levelName));
					break;
				case core::ComponentType::SPRITE:
					name = pComponentData->FirstChildElement("name")->GetText();
					aComponents.push_back(graphics::SpriteComponent::create(name, pLevelLayer));
					break;
				case core::ComponentType::HEROANIMATEDSPRITE:
					// Create HeroAnimatedSpriteComponent
					aComponents.push_back(graphics::HeroAnimatedSpriteComponent::create(pLevelLayer));
					break;
				case core::ComponentType::FIREFLYANIMATEDSPRITE:
					// Create FireflyAnimatedSpriteComponent
					aComponents.push_back(graphics::FireFlyAnimatedSpriteComponent::create(pLevelLayer));
					break;
				case core::ComponentType::NODEOWNER:
					pOwnerData = pComponentData->FirstChildElement("owned");
					if(pOwnerData != nullptr) {
						ownerId = atoi(pOwnerData->GetText());
					}
					aComponents.push_back(game::NodeOwnerComponent::create(nullptr));
					break;
				case core::ComponentType::HEROSOUND:
					aComponents.push_back(sounds::HeroSoundComponent::create());
					break;
				case core::ComponentType::FIREFLYSOUND:
					aComponents.push_back(sounds::FireflySoundComponent::create());
					break;
				default:
					break;
				}
				pComponentData = pComponentData->NextSiblingElement("component");
			}
			aOwnerIds.push_back(ownerId);

			// Add components to the actor
			for(auto component : aComponents) {
				CCLOG("ADD COMPONENT %s TO ACTOR %s", component->getName(), actorType.c_str());
				actor->addComponent(component);
			}

			// Add LightAttrComponent only for fireflies actor
			if(actor->isFirefly()) {
				game::LightAttrComponent* pLightAttrComp = game::LightAttrComponent::create(Color4B::BLACK);
				switch (actor->getActorType()) {
				case core::ActorType::RED_FIREFLY:
					pLightAttrComp->setColor(Color4B::RED);
					break;

				case core::ActorType::GREEN_FIREFLY:
					pLightAttrComp->setColor(Color4B::GREEN);
					break;

				case core::ActorType::BLUE_FIREFLY:
					pLightAttrComp->setColor(Color4B::BLUE);
					break;

				default:
					break;
				}
				actor->addComponent(pLightAttrComp);
			}

			pActorData = pActorData->NextSiblingElement("actor");
		}

		for(int i = 0; i < aOwnerIds.size(); i++) {
			int ownerId = aOwnerIds[i];
			if(ownerId >= 0) {
				game::NodeOwnerComponent* pNodeOwnerComp = dynamic_cast<game::NodeOwnerComponent*>(aActors[i]->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
				if(pNodeOwnerComp != nullptr) {
					pNodeOwnerComp->setOwnedNode(aActors[ownerId]);
				}
			}
		}
	}

	return aActors;
}

physics::CollisionComponent* LevelFactory::__createCollisionComponent(std::string levelName) {
	physics::CollisionComponent* pRet = physics::CollisionComponent::create();
	Image* pBitmask = new Image();
	pBitmask->initWithImageFile(std::string("levels/"+levelName+"/bitmask.png").c_str()); 
	physics::PhysicCollision* pCollision = new physics::PhysicCollision(pBitmask, Point(0, pBitmask->getHeight()));
	pRet->addPhysicCollision(pCollision);

	LightMap* pLM = LightMap::createFromXML(std::string("levels/"+levelName+"/PREC_lightmap.xml").c_str());
	std::vector<core::SynthActor*> lights;
	core::SynthActor* pLight1 = new core::SynthActor(core::ActorType::LIGHT);
	core::SynthActor* pLight2 = new core::SynthActor(core::ActorType::LIGHT);
	core::SynthActor* pLight3 = new core::SynthActor(core::ActorType::LIGHT);
	pLight1->addComponent(game::LightAttrComponent::create(Color4B::RED));
	pLight2->addComponent(game::LightAttrComponent::create(Color4B::BLUE));
	pLight3->addComponent(game::LightAttrComponent::create(Color4B::GREEN));
	lights.push_back(pLight1);
	lights.push_back(pLight2);
	lights.push_back(pLight3);
	physics::LightCollision* pLightCollision = new physics::LightCollision(lights, pLM);
	pRet->addLightCollision(pLightCollision);

	return pRet;
}

std::vector<std::vector<int>> LevelFactory::buildLightsMap(std::string levelName) {
	std::vector<std::vector<int>> voidVec;
	return voidVec;
}

LevelSprite* LevelFactory::buildLevelSprite(std::string levelName, Layer* pLevelLayer, std::vector<core::SynthActor*> aLights) {
	LevelSprite* pRet = LevelSprite::create(std::string("levels/"+levelName+"/bitmask.png").c_str());
	for(int i = 0; i < aLights.size(); i++) {
		game::NodeOwnerComponent* pNodeOwnerComp = dynamic_cast<game::NodeOwnerComponent*>(aLights[i]->getComponent(game::NodeOwnerComponent::COMPONENT_TYPE));
		core::SynthActor* firefly = dynamic_cast<core::SynthActor*>(pNodeOwnerComp->getOwnedNode());
		Color4B color = Color4B(0, 0, 0, 0);
		if(firefly != nullptr) {
			switch (firefly->getActorType()) {
			case core::ActorType::RED_FIREFLY:
				color = Color4B::RED;
				break;
			case core::ActorType::GREEN_FIREFLY:
				color = Color4B::GREEN;
				break;
			case core::ActorType::BLUE_FIREFLY:
				color = Color4B::BLUE;
				break;
			default:
				break;
			}
			pRet->addLight(Sprite::create(std::string("levels/"+levelName+"/PREC_LIGHT_"+std::to_string(i)+".png").c_str())->getTexture(), color);
		}
	}
	pLevelLayer->addChild(pRet, 0, 42);

	return pRet;
}

std::map<std::string,Rect> LevelFactory::buildTriggers(std::string levelName) {
	std::map<std::string,Rect> voidMap;

	// Parse triggers
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile(std::string("levels/"+levelName+"/triggers.xml").c_str());
	if(xmlerror == 0) {
		CCLOG("XML FILE LOADED SUCCESSFULLY : %d", xmlerror);
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pTriggerData, *pOriginData, *pDimensionData;
		std::string triggerType;
		float x, y, width, height = 0;

		pTriggerData = pXMLFile->FirstChildElement("trigger");
		while (pTriggerData) {

			// Get trigger type
			triggerType = pTriggerData->Attribute("type");

			// Get rectangle data
			pOriginData = pTriggerData->FirstChildElement("origin");
			x = pOriginData->FloatAttribute("x");
			y = pOriginData->FloatAttribute("y");
			pDimensionData = pTriggerData->FirstChildElement("dimension");
			width = pDimensionData->FloatAttribute("width");
			height = pDimensionData->FloatAttribute("height");

			// Add new trigger
			voidMap.insert(std::pair<std::string, Rect>(triggerType, Rect(x, y, width, height)));

			pTriggerData = pTriggerData->NextSiblingElement("trigger");
		}
	}

	return voidMap;
}

}  // namespace game
