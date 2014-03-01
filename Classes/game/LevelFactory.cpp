/*!
 * \file LevelFactory.cpp
 * \brief Singleton dealing with the creation of actors, light maps, level sprites, triggers
 * \author Xopi
 * \date 26/02/2014
 */
#include "LevelFactory.h"
#include "physics/GeometryComponent.h"
#include "physics/MovementComponent.h"
#include "graphics/HeroAnimatedSpriteComponent.h"

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

std::vector<core::SynthActor*> LevelFactory::buildActors(/*core::xml data, */Layer* pLevelLayer) {
	std::vector<core::SynthActor*> aActors; 
	std::vector<core::SynthComponent*> aComponents; 

	// invert enum actor type
	_actorTagsMap.insert(std::pair<std::string, core::ActorType>("HERO",		core::ActorType::HERO));
	_actorTagsMap.insert(std::pair<std::string, core::ActorType>("FIREFLY",		core::ActorType::FIREFLY));
	_actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHT",		core::ActorType::LIGHT));
	_actorTagsMap.insert(std::pair<std::string, core::ActorType>("LIGHTSWITCH",	core::ActorType::LIGHTSWITCH));

	_componentTagsMap.insert(std::pair<std::string, core::ComponentType>("GEOMETRY",			core::ComponentType::GEOMETRY));
	_componentTagsMap.insert(std::pair<std::string, core::ComponentType>("MOVEMENT",			core::ComponentType::MOVEMENT));
	_componentTagsMap.insert(std::pair<std::string, core::ComponentType>("COLLISION",			core::ComponentType::COLLISION));
	_componentTagsMap.insert(std::pair<std::string, core::ComponentType>("HEROANIMATEDSPRITE",	core::ComponentType::HEROANIMATEDSPRITE));

	// parsing actors
	tinyxml2::XMLDocument* pXMLFile = new tinyxml2::XMLDocument();
	int xmlerror = pXMLFile->LoadFile("xml/actors.xml");
	if(xmlerror == 0) {
		CCLOG("XML FILE LOADED SUCCESSFULLY : %d", xmlerror);
		tinyxml2::XMLHandle hDoc(pXMLFile);
		tinyxml2::XMLElement *pActorData, *pComponentData, *pPositionData, *pSizeData, *pRotateData, *pAnchorPointData, *pAccelerationData, *pGravityData;
		std::string actorType, componentType;
		float positionX, positionY, anchorPointX, anchorPointY, rotate, accelerationX, accelerationY, gravityX, gravityY, width, height = 0;
		bool bIsLoop = false;
		std::string pos = "";

		pActorData = pXMLFile->FirstChildElement("actor");
		while (pActorData) {
			actorType = pActorData->Attribute("type");
			pComponentData = pActorData->FirstChildElement("component");
			// Create components
			while(pComponentData) {
				componentType = pComponentData->Attribute("type");
				switch(_componentTagsMap[componentType]) {
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
				case core::ComponentType::COLLISION:
					// Create CollisionComponent
					aComponents.push_back(__createCollisionComponent());
					break;
				case core::ComponentType::HEROANIMATEDSPRITE:
					// Create HeroAnimatedSpriteComponent
					aComponents.push_back(graphics::HeroAnimatedSpriteComponent::create(pLevelLayer));
					break;
				default:
					break;
				}
				pComponentData = pComponentData->NextSiblingElement("component");
			}

			// Create actor
			core::SynthActor* actor = new core::SynthActor(_actorTagsMap[actorType]);
			aActors.push_back(actor);

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

std::map<std::string,Rect> LevelFactory::buildTriggers(core::xml data) {
	std::map<std::string,Rect> voidMap;
	return voidMap;
}

}  // namespace game
