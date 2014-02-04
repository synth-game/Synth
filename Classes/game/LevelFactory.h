#ifndef GAME_LEVEL_FACTORY_H
#define GAME_LEVEL_FACTORY_H

#include "vector.h"
#include "map.h"
#include "Game/LevelSprite.h"
#include "Game/Rect.h"
#include "Core/SynthActor.h"
#include "System/xml.h"

namespace Game
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

	vector<SynthActor*> buildActors(System::xml data);

	vector<vector<int>> buildLightsMap(System::xml data);

	LevelSprite* buildLevelSprite(System::xml data);

	map<string,Rect> buildTriggers(System::xml data);

};

}  // namespace Game
#endif
