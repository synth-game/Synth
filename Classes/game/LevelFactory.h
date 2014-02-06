#ifndef GAME_LEVEL_FACTORY_H
#define GAME_LEVEL_FACTORY_H

#include <vector>
#include <map>
#include "Game/LevelSprite.h"
#include "Game/Rect.h"
#include "Core/SynthActor.h"
#include "System/xml.h"

namespace game
{
class LevelFactory
{
private:
	/**
	 *
	 */
	LevelFactory();

public:
	~LevelFactory();

	static LevelFactory* getInstance();

	std::vector<SynthActor*> buildActors(synthsystem::xml data);

	std::vector<std::vector<int>> buildLightsMap(synthsystem::xml data);

	LevelSprite* buildLevelSprite(synthsystem::xml data);

	std::map<std::string,Rect> buildTriggers(synthsystem::xml data);

};

}  // namespace game
#endif
