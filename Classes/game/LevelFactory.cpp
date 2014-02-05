#include "LevelFactory.h"

namespace game
{

LevelFactory::LevelFactory()
{
}

LevelFactory::~LevelFactory()
{
}

LevelFactory* LevelFactory::getInstance()
{
	return 0;
}

vector<SynthActor*> LevelFactory::buildActors(system::xml data)
{
	return 0;
}

vector<vector<int>> LevelFactory::buildLightsMap(system::xml data)
{
	return 0;
}

LevelSprite* LevelFactory::buildLevelSprite(system::xml data)
{
	return 0;
}

std::map<string,Rect> LevelFactory::buildTriggers(system::xml data)
{
	return 0;
}
}  // namespace game
