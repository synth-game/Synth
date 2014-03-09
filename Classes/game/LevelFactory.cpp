/*!
 * \file LevelFactory.cpp
 * \brief Singleton dealing with the creation of actors, light maps, level sprites, triggers
 * \author Xopi
 * \date 26/02/2014
 */
#include "LevelFactory.h"
#include "game/NodeOwnerComponent.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "physics/FollowMovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"
#include "graphics/FireFlyAnimatedSpriteComponent.h"

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

	// parsing actors
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile(std::string("levels/"+levelName+"/actors.xml").c_str());
	if(xmlerror == 0) {
		CCLOG("XML FILE LOADED SUCCESSFULLY : %d", xmlerror);
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pActorData, *pComponentData, *pPositionData, *pSizeData, *pRotateData, *pAnchorPointData, *pAccelerationData, *pGravityData;
		std::string actorType, componentType, name;
		float positionX, positionY, anchorPointX, anchorPointY, rotate, accelerationX, accelerationY, gravityX, gravityY, width, height = 0;

		pActorData = pXMLFile->FirstChildElement("actor");
		while (pActorData) {

			// Create actor
			actorType = pActorData->Attribute("type");
			core::SynthActor* actor = new core::SynthActor(actorTagsMap[actorType]);
			aActors.push_back(actor);

			// Create components
			std::vector<core::SynthComponent*> aComponents;
			pComponentData = pActorData->FirstChildElement("component");

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
					aComponents.push_back(physics::MovementComponent::create(Point(accelerationX, accelerationY), Point(gravityX, gravityY)));
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
					aComponents.push_back(__createCollisionComponent());
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
					aComponents.push_back(game::NodeOwnerComponent::create(nullptr));
				default:
					break;
				}
				pComponentData = pComponentData->NextSiblingElement("component");
			}

			// Add components to the actor
			for(auto component : aComponents) {
				CCLOG("ADD COMPONENT %s TO ACTOR %s", component->getName(), actorType.c_str());
				actor->addComponent(component);
			}

			pActorData = pActorData->NextSiblingElement("actor");
		}
	}
	else {
		CCLOG("ERROR WHILE LOADING XML FILE : %d", xmlerror);
	}

	return aActors;
}

physics::CollisionComponent* LevelFactory::__createCollisionComponent() {
	physics::CollisionComponent* pRet = physics::CollisionComponent::create();
	Image* pBitmask = new Image();
	pBitmask->initWithImageFile("levels/test/bitmask.png"); 
	physics::PhysicCollision* pCollision = new physics::PhysicCollision(pBitmask, Point(0, pBitmask->getHeight()));
	pRet->addPhysicCollision(pCollision);
	return pRet;
}

std::vector<std::vector<int>> LevelFactory::buildLightsMap(core::xml data) {
	std::vector<std::vector<int>> voidVec;
	return voidVec;
}

LevelSprite* LevelFactory::buildLevelSprite(core::xml data) {
	return nullptr;
}

std::map<std::string,Rect> LevelFactory::buildTriggers(std::string levelName) {
	std::map<std::string,Rect> voidMap;

	// Parse triggers
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile(std::string("levels/"+levelName+"/actors.xml").c_str());
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
