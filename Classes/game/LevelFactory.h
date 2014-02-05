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

	vector<SynthActor*> buildActors(System::xml data);

	vector<vector<int>> buildLightsMap(System::xml data);

	LevelSprite* buildLevelSprite(System::xml data);

	std::map<string,Rect> buildTriggers(System::xml data);

};

}  // namespace game
#endif
