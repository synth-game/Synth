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

	vector<SynthActor*> buildActors(system::xml data);

	vector<vector<int>> buildLightsMap(system::xml data);

	LevelSprite* buildLevelSprite(system::xml data);

	std::map<string,Rect> buildTriggers(system::xml data);

};

}  // namespace game
#endif
