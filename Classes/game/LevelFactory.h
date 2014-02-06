#ifndef GAME_LEVEL_FACTORY_H
#define GAME_LEVEL_FACTORY_H

#include <vector>
#include <map>
#include "game/LevelSprite.h"
#include "core/SynthActor.h"
#include "core/SynthConfig.h"



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

	std::vector<core::SynthActor*> buildActors(core::xml data);

	std::vector<std::vector<int>> buildLightsMap(core::xml data);

	LevelSprite* buildLevelSprite(core::xml data);

	std::map<std::string,Rect> buildTriggers(core::xml data);

};

}  // namespace game
#endif
