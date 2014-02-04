#include "LevelFactory.h"

namespace Game
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

vector<SynthActor*> LevelFactory::buildActors(System::xml data)
{
	return 0;
}

vector<vector<int>> LevelFactory::buildLightsMap(System::xml data)
{
	return 0;
}

LevelSprite* LevelFactory::buildLevelSprite(System::xml data)
{
	return 0;
}

std::map<string,Rect> LevelFactory::buildTriggers(System::xml data)
{
	return 0;
}
}  // namespace Game
