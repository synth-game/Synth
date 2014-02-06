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

std::vector<core::SynthActor*> LevelFactory::buildActors(core::xml data)
{
	std::vector<core::SynthActor*> voidVec;
	return voidVec;
}

std::vector<std::vector<int>> LevelFactory::buildLightsMap(core::xml data)
{
	std::vector<std::vector<int>> voidVec;
	return voidVec;
}

LevelSprite* LevelFactory::buildLevelSprite(core::xml data)
{
	return nullptr;
}

std::map<std::string,Rect> LevelFactory::buildTriggers(core::xml data)
{
	std::map<std::string,Rect> voidMap;
	return voidMap;
}
}  // namespace game
