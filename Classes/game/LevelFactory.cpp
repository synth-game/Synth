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

std::vector<SynthActor*> LevelFactory::buildActors(synthsystem::xml data)
{
	return 0;
}

std::vector<std::vector<int>> LevelFactory::buildLightsMap(synthsystem::xml data)
{
	return 0;
}

LevelSprite* LevelFactory::buildLevelSprite(synthsystem::xml data)
{
	return 0;
}

std::map<std::string,Rect> LevelFactory::buildTriggers(synthsystem::xml data)
{
	return 0;
}
}  // namespace game
