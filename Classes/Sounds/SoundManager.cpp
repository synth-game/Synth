#include "SoundManager.h"

namespace sounds
{



SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

SoundManager* SoundManager::getInstance()
{
	return 0;
}

void SoundManager::init(core::xml data)
{
}

bool SoundManager::playSound(std::string soundName, int iTrackId)
{
	return 0;
}

bool SoundManager::stopSound(int iTrackId)
{
	return 0;
}

bool SoundManager::unmuteMusic(std::string musicName)
{
	return 0;
}

bool SoundManager::muteMusic(std::string musicName)
{
	return 0;
}

bool SoundManager::isFinished(int iTrackId)
{
	return 0;
}

void SoundManager::refresh()
{
}
}  // namespace sounds
