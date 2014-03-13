/*!
 * \file LevelFactory.h
 * \brief Singleton dealing with the creation of actors, light maps, level sprites, triggers
 * \author Xopi
 * \date 26/02/2014
 */
#ifndef GAME_LEVEL_FACTORY_H
#define GAME_LEVEL_FACTORY_H

#include <vector>
#include <map>
#include "cocos2d.h"
#include "game/LevelSprite.h"
#include "core/SynthActor.h"
#include "core/ActorType.h"
#include "core/SynthComponent.h"
#include "core/ComponentType.h"
#include "physics/CollisionComponent.h"
#include "core/SynthConfig.h"



namespace game {

class LevelFactory {

public:
	/*
	 * Methods
	 */

	/*! \brief Destructor */
	~LevelFactory();

	static LevelFactory* getInstance();

	std::vector<core::SynthActor*> buildActors(std::string levelName, Layer* pLevelLayer);

	std::vector<std::vector<int>> buildLightsMap(std::string levelName);

	LevelSprite* buildLevelSprite(std::string levelName, Layer* pLevelLayer, std::vector<core::SynthActor*> aLights);

	std::map<std::string,Rect> buildTriggers(std::string levelName);

private:
	/*
	 * Methods
	 */
	physics::CollisionComponent* __createCollisionComponent(std::string levelName);

	/*! \brief Constructor */
	LevelFactory();

	/*
	 * Members
	 */
	
	/*! \brief The singleton instance */
	static LevelFactory* _pInstance;
};

}  // namespace game
#endif
